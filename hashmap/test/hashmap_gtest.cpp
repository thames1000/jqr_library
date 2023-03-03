#include <gtest/gtest.h>
#include "hashmap.h"
#include "exit_codes.h"

TEST(BaseTest, Initialize_and_Destroy_Func)
{
    hash_table_t *h_table = hash_table_init(20, NULL);
    EXPECT_NE(h_table, nullptr);
    exit_code_t ret_val = hash_table_destroy(h_table);
    EXPECT_EQ(ret_val, E_SUCCESS);
}