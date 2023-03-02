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

/*
 * Thread Pool Struct
 */
typedef struct thread_pool
{
    atomic_uint_fast8_t keep_alive;  // flag for keeping threads active (1 or 0)
    atomic_uint_fast8_t num_threads; // number of threads currently active
    int max_threads;                 // initial Max thread count
    queue_t *work_queue;             // Queue for work to be added to
    pthread_t **thread_list;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    pthread_condattr_t cattr;
    void (*work_function)(void *);
} thread_pool_t;

void *startThread(void *thread_pool)
{
    thread_pool_t *tpool = (thread_pool_t *)thread_pool;
    for (;;)
    {
        pthread_mutex_lock(&tpool->mutex);
        while (0 == size_of_queue(tpool->work_queue))
        {
            if (0 == tpool->keep_alive)
            {
                pthread_mutex_unlock(&tpool->mutex);
                tpool->num_threads--;
                return NULL;
            }
            pthread_cond_wait(&tpool->condition, &tpool->mutex);
        }
        void *work = dequeue(tpool->work_queue);
        pthread_mutex_unlock(&tpool->mutex);
        if (NULL != tpool->work_function)
        {
            tpool->work_function(work);
        }
    }
    return NULL;
}

/*
 * Thread Pool Struct Init
 */
thread_pool_t *tpool_init(int threads, void (*work_func)(void *))
{
    thread_pool_t *tpool = calloc(1, sizeof(*tpool));
    CHECK_NULL(tpool, goto CLEANUP);

    tpool->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    tpool->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    tpool->work_queue = queue_init(NULL, NULL, NULL);
    CHECK_NULL(tpool->work_queue, goto TPOOL_CLEANUP);

    tpool->thread_list = calloc(threads, sizeof(pthread_t *));
    CHECK_NULL(tpool->thread_list, goto QUEUE_CLEANUP);

    tpool->keep_alive = 1;
    tpool->num_threads = threads;
    tpool->max_threads = threads;

    tpool->work_function = work_func;
    for (int i = 0; i < threads; i++)
    {
        if (0 != pthread_create(&(tpool->thread_list[i]), NULL, startThread, tpool))
        {
            fprintf(stderr, "Failed to create thread %d\n", i);
        }
    }
    return tpool;
QUEUE_CLEANUP:
    queue_destroy(tpool->work_queue);
TPOOL_CLEANUP:
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
    if (NULL == tpool)
    {
        fprintf(stderr, "Nothing to destroy\n");
        return E_NULL_POINTER;
    }
    shutdown(tpool);
    free(tpool->thread_list);
    queue_destroy(tpool->work_queue);
    free(tpool);
    return E_SUCCESS;
}

void tpool_add_work(thread_pool_t *tpool, void *work)
{
    if (NULL != tpool->work_queue)
    {
        pthread_mutex_lock(&tpool->mutex);
        enqueue(tpool->work_queue, work);
        pthread_mutex_unlock(&tpool->mutex);
        pthread_cond_signal(&tpool->condition);
    }
}
