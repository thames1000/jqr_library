#include <gtest/gtest.h>
#include "hashmap.h"
#include "exit_codes.h"
typedef struct data_point data_point_t;
struct data_point
{
    void *data;
    data_point_t *overflow;
};

typedef struct hash_table
{
    data_point_t **table;
    uint64_t max_size;
    uint64_t spots_used;
    uint64_t items_in_table;
    void (*free_func)(void *);
    void (*print_func)(void *);
} hash_table_t;

void print_string(void *data)
{
    char *temp = (char *)data;
    printf("%s", temp);
}

TEST(BaseTest, Initialize_and_Destroy_Func)
{
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    EXPECT_NE(h_table, nullptr);
    exit_code_t ret_val = hash_table_destroy(h_table);
    EXPECT_EQ(ret_val, E_SUCCESS);
}

TEST(BaseTest, Insert_Func)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    exit_code_t ret_val = hash_insert(temp, 15, h_table);
    EXPECT_EQ(ret_val, E_SUCCESS);
    EXPECT_EQ(h_table->spots_used, 1);
    display(h_table);
    ret_val = hash_table_destroy(h_table);
    EXPECT_EQ(ret_val, E_SUCCESS);
}

TEST(BaseTest, Insert_Twice)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert(temp, 15, h_table);
    hash_insert(temp, 15, h_table);
    EXPECT_EQ(h_table->spots_used, 1);
    EXPECT_EQ(h_table->items_in_table, 2);
    for (int i = 0; i < 20; i++)
    {
        if (NULL != h_table->table[i])
        {
            EXPECT_NE(h_table->table[i]->overflow, nullptr);
        }
    }
    display(h_table);
    exit_code_t ret_val = hash_table_destroy(h_table);
    EXPECT_EQ(ret_val, E_SUCCESS);
}

TEST(BaseTest, Insert_Five)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert(temp, 15, h_table);
    hash_insert(temp, 15, h_table);
    hash_insert(temp, 15, h_table);
    hash_insert(temp, 15, h_table);
    hash_insert(temp, 15, h_table);
    EXPECT_EQ(h_table->spots_used, 1);
    EXPECT_EQ(h_table->items_in_table, 5);
    for (int i = 0; i < 20; i++)
    {
        if (NULL != h_table->table[i])
        {
            EXPECT_NE(h_table->table[i]->overflow, nullptr);
        }
    }
    display(h_table);
    exit_code_t ret_val = hash_table_destroy(h_table);
    EXPECT_EQ(ret_val, E_SUCCESS);
}