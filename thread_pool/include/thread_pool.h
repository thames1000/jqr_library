#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "exit_codes.h"
    typedef struct thread_pool thread_pool_t;

    /**
     * @brief
     *
     * @param threads - number of threads to be made
     * @param work_func - Function that each thread should perform
     * @return thread_pool_t*
     */
    thread_pool_t *tpool_init(const int threads);

    /**
     * @brief
     *
     * @param tpool
     * @return exit_code_t
     */
    exit_code_t tpool_destroy(thread_pool_t *tpool);

    /**
     * @brief
     *
     * @param tpool
     * @param work
     * @param free_func - Function for freeing the arg for the jobs
     */
    void tpool_add_work(thread_pool_t *tpool, void *work, void (*work_function)(void *), void (*free_func)(void *));

#ifdef __cplusplus
}
#endif

#endif