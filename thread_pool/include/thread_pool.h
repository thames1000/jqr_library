#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <exit_codes.h>
struct thread_pool;
typedef struct thread_pool thread_pool_t;

typedef void (*thread_func_t)(void *arg);

thread_pool_t *thread_pool_init(size_t thread_count);
exit_code_t thread_pool_destroy(thread_pool_t *t_pool);

exit_code_t thread_pool_add_work(thread_pool_t *t_pool, thread_func_t func, void *arg);
exit_code_t thread_pool_wait(thread_pool_t *t_pool);

#ifdef __cplusplus
}
#endif

#endif