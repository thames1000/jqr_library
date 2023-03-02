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

typedef struct thread_func
{
    void (*function)(void *);
} thread_func_t;

/*
 * Thread Pool Struct
 */
typedef struct thread_pool
{
    atomic_uint_fast8_t keep_alive;
    atomic_uint_fast8_t num_threads;
    int max_threads;
    queue_t *work_queue;
    atomic_uint_fast64_t job_count;
    pthread_t **thread_list;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
    pthread_condattr_t cattr;
} thread_pool_t;

void *startThread(void *thread_pool)
{
    debug_print("startThread Called%s \n", "");
    thread_pool_t *tpool = (thread_pool_t *)thread_pool;

    while (0 != atomic_load(&tpool->keep_alive))
    {
        pthread_mutex_lock(&tpool->mutex);
        if (atomic_load(&tpool->job_count))
        {
            pthread_cond_wait(&tpool->condition, &tpool->mutex);
            pthread_mutex_unlock(&tpool->mutex);
            continue;
        }
        void *work = dequeue(tpool->work_queue);
        pthread_mutex_unlock(&(tpool->mutex));
        // work->work_func; ###### DO WORK #######
    }
    atomic_fetch_sub(&tpool->num_threads, 1);
}

/*
 * Thread Pool Struct Init
 */
thread_pool_t *tpool_init(int threads, void (*free_func)(void *))
{
    thread_pool_t *tpool = calloc(1, sizeof(*tpool));
    CHECK_NULL(tpool, goto CLEANUP);

    tpool->mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    tpool->condition = (pthread_cond_t)PTHREAD_COND_INITIALIZER;

    tpool->work_queue = queue_init(free_func, NULL, NULL);
    CHECK_NULL(tpool->work_queue, goto TPOOL_CLEANUP);

    tpool->thread_list = calloc(threads, sizeof(pthread_t *));
    CHECK_NULL(tpool->thread_list, goto QUEUE_CLEANUP);

    tpool->keep_alive = 1;
    tpool->num_threads = threads;
    tpool->max_threads = threads;

    tpool->job_count = 0;

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

exit_code_t shutdown(thread_pool_t *tpool)
{
    CHECK_NULL(tpool, return E_NULL_POINTER);
    atomic_fetch_sub(&tpool->keep_alive, 1);

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
    exit_code_t ret_val = shutdown(tpool);
    if (NULL == tpool)
    {
        fprintf(stderr, "Nothing to destroy\n");
        return E_NULL_POINTER;
    }
    free(tpool->thread_list);
    queue_destroy(tpool->work_queue);
    free(tpool);
    return E_SUCCESS;
}

// Shutdown
/*
 * Worker Function
 * # while(atomic_load(keep_alive))
 * # {
 * #    pthread_mutex_lock(mutex);
 * #    if (atomic_load(empty_queue))
 * #    {
 * #        mutex_wait(condition);
 * #        pthread_mutex_unlock(mutex);
 * #        continue;
 * #    }
 * #    work = dequeue(work_queue);
 * #    pthread_mutex_unlock(mutex);
 * #    work->work_func; ###### DO WORK #######
 * # }
 * # --num_threads;
 * # return NULL;
 */

/*
 * Add to Queue
 * # pthread_mutex_lock(mutex);
 * # enqueue(work_queue, work);
 * # pthread_mutex_unlock(mutex);
 * # pthread_signal(condition);
 */
