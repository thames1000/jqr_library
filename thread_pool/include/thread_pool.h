#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "exit_codes.h"
    typedef struct thread_pool thread_pool_t;
    thread_pool_t *tpool_init(int threads, void (*free_func)(void *));
    exit_code_t shutdown(thread_pool_t *tpool);
    exit_code_t tpool_destroy(thread_pool_t *tpool);

#ifdef __cplusplus
}
#endif

#endif