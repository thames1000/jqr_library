#include <gtest/gtest.h>
#include "thread_pool.h"
#include "exit_codes.h"

TEST(BaseTest, Initialize_and_Destroy_Func)
{
    thread_pool_t *tpool = tpool_init(3, NULL);
    EXPECT_NE(tpool, nullptr);
    exit_code_t ret_val = tpool_destroy(tpool);
    EXPECT_EQ(ret_val, E_SUCCESS);
}
