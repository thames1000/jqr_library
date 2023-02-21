#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <thread_pool.h>


struct tpool_work {
    thread_func_t func;
    void *arg;
    struct tpool_work *next;
};
typedef struct tpool_work tpool_work_t;

struct thread_pool {
    tpool_work_t *work_first;
    tpool_work_t *work_last;
    pthread_mutex_t work_mutex;
    pthread_cond_t work_cond;
    pthread_cond_t working_cond;
    size_t working_cnt;
    size_t thread_cnt;
    bool stop;
};