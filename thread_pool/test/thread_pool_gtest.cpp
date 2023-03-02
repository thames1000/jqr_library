#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"
#include "exit_codes.h"

typedef struct temp
{
    int a;
    int b;
} temp_t;

void add_stuff(void *temp_val)
{
    temp_t *temp = (temp_t *)temp_val;
    printf("%d + %d = %d\n", temp->a, temp->b, temp->a + temp->b);
}

TEST(BaseTest, Initialize_and_Destroy_Func)
{
    thread_pool_t *tpool = tpool_init(3, NULL);
    EXPECT_NE(tpool, nullptr);
    exit_code_t ret_val = tpool_destroy(tpool);
    EXPECT_EQ(ret_val, E_SUCCESS);
}

TEST(BaseTest, Add_Five_Jobs)
{
    temp_t *val = (temp_t *)calloc(1, sizeof(temp_t));
    val->a = 2;
    val->b = 5;
    thread_pool_t *tpool = tpool_init(5, add_stuff);
    tpool_add_work(tpool, val);
    tpool_add_work(tpool, val);
    tpool_add_work(tpool, val);
    tpool_add_work(tpool, val);
    tpool_add_work(tpool, val);
    tpool_add_work(tpool, val);
    tpool_add_work(tpool, val);
    tpool_add_work(tpool, val);
    tpool_destroy(tpool);
    free(val);
}
