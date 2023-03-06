#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "exit_codes.h"
    typedef struct thread_pool thread_pool_t;

    /**
     * @brief Initialization function
     *
     * @param threads number of threads to be made
     * @return thread_pool_t*
     */
    thread_pool_t *tpool_init(const int threads);

    /**
     * @brief Destroy function for the thread_pool_t
     *
     * @param tpool thread_pool_t object pointer to be destroyed
     * @return exit_code_t returns E_SUCCESS on successful destroy. returns E_NULL_POINTER if tpool is NULL
     */
    exit_code_t tpool_destroy(thread_pool_t *tpool);

    /**
     * @brief
     *
     * @param tpool thread_pool_t object that work needs to be added to
     * @param work argument for work_function
     * @param work_function Function to be called by the thread
     * @param free_func Function for freeing the arg for the jobs
     */
    void tpool_add_work(thread_pool_t *tpool, void *arg, void (*work_function)(void *), void (*free_func)(void *));

#ifdef __cplusplus
}
#endif

#endif