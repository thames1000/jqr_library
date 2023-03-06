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
void sub_stuff(void *temp_val)
{
    temp_t *temp = (temp_t *)temp_val;
    printf("%d - %d = %d\n", temp->a, temp->b, temp->a - temp->b);
}
void mul_stuff(void *temp_val)
{
    temp_t *temp = (temp_t *)temp_val;
    printf("%d * %d = %d\n", temp->a, temp->b, temp->a * temp->b);
}
void div_stuff(void *temp_val)
{
    temp_t *temp = (temp_t *)temp_val;
    printf("%d / %d = %d\n", temp->a, temp->b, temp->a / temp->b);
}

TEST(BaseTest, Initialize_and_Destroy_Func)
{
    thread_pool_t *tpool = tpool_init(3);
    EXPECT_NE(tpool, nullptr);
    exit_code_t ret_val = tpool_destroy(tpool);
    EXPECT_EQ(ret_val, E_SUCCESS);
}

TEST(BaseTest, Add_Jobs)
{
    temp_t *val = (temp_t *)calloc(1, sizeof(temp_t));
    val->a = 6;
    val->b = 3;
    thread_pool_t *tpool = tpool_init(4);
    tpool_add_work(tpool, val, add_stuff, NULL);
    tpool_add_work(tpool, val, sub_stuff, NULL);
    tpool_add_work(tpool, val, mul_stuff, NULL);
    tpool_add_work(tpool, val, div_stuff, NULL);
    tpool_destroy(tpool);
    free(val);
}
