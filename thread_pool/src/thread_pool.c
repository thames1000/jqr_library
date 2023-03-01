#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "queue.h"
#include "thread_pool.h"

#define CHECK_NULL(x, action) \
    if (NULL == x)            \
        action;

typedef struct thread_func
{
    void (*function)(void *);
} thread_func_t;

/*
 * Thread Pool Struct
 */
typedef struct thread_pool
{
    atomic_bool keep_alive;
    atomic_uint_fast8_t num_threads;
    int max_threads;
    queue_t *work_queue;
    atomic_uint_fast64_t job_count;
    pthread_t **thread_list;
    pthread_mutex_t wait_mutex;
    pthread_mutex_t queue_mutex;
    pthread_cond_t condition;
    pthread_condattr_t cattr;
} thread_pool_t;

void *startThread(thread_pool_t *tpool)
{
    while (atomic_load(&(tpool->keep_alive)))
    {
        pthread_mutex_lock(&(tpool->wait_mutex));
        if (atomic_load(&(tpool->job_count)))
        {
            pthread_cond_wait(&(tpool->condition), &(tpool->wait_mutex));
            pthread_mutex_unlock(&(tpool->wait_mutex));
            continue;
        }
        void *work = dequeue(tpool->work_queue);
        pthread_mutex_unlock(&(tpool->wait_mutex));
        // work->work_func; ###### DO WORK #######
    }
    --(tpool->num_threads);
    return NULL;
}

/*
 * Thread Pool Struct Init
 */
thread_pool_t *tpool_init(int threads, void (*free_func)(void *),
                          int (*compare_func)(void *, void *),
                          void (*print_func)(void *))
{
    thread_pool_t *tpool = NULL;
    pthread_mutex_t wait_mutex;
    pthread_mutex_t queue_mutex;
    pthread_cond_t condition;
    pthread_condattr_t cattr;
    if (0 != pthread_mutex_init(&wait_mutex, NULL))
    {
        goto CLEANUP;
    }
    if (0 != pthread_mutex_init(&queue_mutex, NULL))
    {
        goto CLEANUP;
    }
    if (0 != pthread_condattr_init(&cattr))
    {
        goto CLEANUP;
    }
    if (0 != pthread_cond_init(&condition))
    {
        goto CLEANUP;
    }

    queue_t *work_queue = queue_init(free_func, compare_func, print_func);
    CHECK_NULL(work_queue, goto CLEANUP);

    pthread_t **thread_list = (pthread_t **)calloc(threads, sizeof(pthread_t *));
    CHECK_NULL(thread_list, goto CLEANUP);
    for (int i = 0; i < threads; i++)
    {
        if (0 != pthread_create(thread_list))
    }
    atomic_bool keep_alive = true;
    atomic_uint_fast8_t num_threads = threads;
    int max_threads = threads;
    atomic_uint_fast64_t job_count = 0;
    thread_pool_t *tpool = (thread_pool_t *)calloc(1, sizeof(thread_pool_t));
    CHECK_NULL(tpool, goto CLEANUP);
    tpool->keep_alive = keep_alive;
    tpool->num_threads = num_threads;
    tpool->max_threads = max_threads;
    tpool->work_queue = work_queue;
    tpool->job_count = job_count;
    tpool->thread_list = thread_list;
    tpool->wait_mutex = wait_mutex;
    tpool->queue_mutex = queue_mutex;
    tpool->condition = condition;
    tpool->cattr = cattr;
CLEANUP:
    return tpool;
}

/*
 * Thread Pool Struct Destroy
 */
thread_pool_t *tpool_destroy(thread_pool_t *tpool)
{
}

/*
 * Shutdown
 * # atomic_store(keep_alive, false);
 * # while (0 != num_threads)
 * # {
 * #    pthread_signal(condition);
 * # }
 */

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

/*
 * Boss Shutdown
 * # for (int i = 0; i < max_threads; ++i)
 * # {
 * #    pthread_mutex_join(thread_list[i], NULL);
 * # }
 */