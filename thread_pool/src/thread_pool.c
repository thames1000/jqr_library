#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdlib.h>
#include "queue.h"
#include "thread_pool.h"
#ifdef NDEBUG
#define DEBUG_PRINT 0
#else
#define DEBUG_PRINT 1
#endif

#define CHECK_NULL(x, action) \
    if (NULL == x)            \
        action;

#define debug_print(fmt, ...)                  \
    do                                         \
    {                                          \
        if (DEBUG_PRINT)                       \
            fprintf(stderr, fmt, __VA_ARGS__); \
    } while (0)

typedef struct job
{
    void *arg;
    void (*worker_function)(void *);
    void (*free_func)(void *);
} job_t;
/*
 * Thread Pool Struct
 */
typedef struct thread_pool
{
    atomic_uint_fast8_t keep_alive;  // flag for keeping threads active (1 or 0)
    atomic_uint_fast8_t num_threads; // number of threads currently active
    int max_threads;                 // initial Max thread count
    queue_t *work_queue;             // Queue for work to be added to
    pthread_t *thread_list;          // List of active threads
    pthread_mutex_t mutex;
    pthread_cond_t condition;
} thread_pool_t;

static void *startThread(void *thread_pool)
{
    thread_pool_t *tpool = (thread_pool_t *)thread_pool;
    if (NULL == tpool)
    {
        goto END;
    }
    for (;;)
    {
        pthread_mutex_lock(&tpool->mutex);
        while (0 == size_of_queue(tpool->work_queue))
        {
            if (0 == tpool->keep_alive)
            {
                pthread_mutex_unlock(&tpool->mutex);
                tpool->num_threads--;
                goto END;
            }
            pthread_cond_wait(&tpool->condition, &tpool->mutex);
        }
        job_t *job = dequeue(tpool->work_queue);

        pthread_mutex_unlock(&tpool->mutex);
        if (NULL != job->worker_function)
        {
            job->worker_function(job->arg);
        }
        if (NULL != job->free_func)
        {
            job->free_func(job->arg);
        }
        free(job);
    }
END:
    return NULL;
}

/*
 * Thread Pool Struct Init
 */
thread_pool_t *tpool_init(const int threads)
{
    thread_pool_t *tpool = calloc(1, sizeof(*tpool));
    CHECK_NULL(tpool, goto CLEANUP);

    if (0 != pthread_mutex_init(&tpool->mutex, NULL))
    {
        fprintf(stderr, "Mutex init error\n");
        goto MUTEX_FAILURE;
    }
    if (0 != pthread_cond_init(&tpool->condition, NULL))
    {
        fprintf(stderr, "condition init error\n");
        goto COND_FAILURE;
    }

    tpool->work_queue = queue_init(NULL, NULL, NULL);
    CHECK_NULL(tpool->work_queue, goto QUEUE_FAILURE);

    tpool->thread_list = calloc(threads, sizeof(pthread_t));
    CHECK_NULL(tpool->thread_list, goto THREAD_LIST_FAILURE);

    tpool->keep_alive = 1;
    tpool->num_threads = threads;
    tpool->max_threads = threads;

    for (int i = 0; i < threads; i++)
    {
        if (0 != pthread_create(&tpool->thread_list[i], NULL, startThread, tpool))
        {
            fprintf(stderr, "Failed to create thread %d\n", i);
        }
    }
    return tpool;
THREAD_LIST_FAILURE:
    queue_destroy(tpool->work_queue);
QUEUE_FAILURE:
    pthread_mutex_destroy(&tpool->mutex);
MUTEX_FAILURE:
    pthread_cond_destroy(&tpool->condition);
COND_FAILURE:
    free(tpool);
CLEANUP:
    return NULL;
}

static exit_code_t shutdown(thread_pool_t *tpool)
{
    CHECK_NULL(tpool, return E_NULL_POINTER);
    tpool->keep_alive--;

    pthread_cond_broadcast(&tpool->condition);

    for (int i = 0; i < tpool->max_threads; i++)
    {
        pthread_join(tpool->thread_list[i], NULL);
    }
    return E_SUCCESS;
}

/*
 * Thread Pool Struct Destroy
 */
exit_code_t tpool_destroy(thread_pool_t *tpool)
{
    CHECK_NULL(tpool, return E_NULL_POINTER);
    shutdown(tpool);
    free(tpool->thread_list);
    queue_destroy(tpool->work_queue);
    free(tpool);
    return E_SUCCESS;
}

void tpool_add_work(thread_pool_t *tpool, void *arg, void (*work_function)(void *), void (*free_func)(void *))
{
    job_t *new_job = calloc(1, sizeof(*new_job));
    if (NULL == new_job)
    {
        return;
    }
    new_job->arg = arg;
    new_job->worker_function = work_function;
    new_job->free_func = free_func;
    if (NULL != tpool->work_queue)
    {
        pthread_mutex_lock(&tpool->mutex);
        enqueue(tpool->work_queue, new_job);
        pthread_mutex_unlock(&tpool->mutex);
        pthread_cond_signal(&tpool->condition);
    }
}
