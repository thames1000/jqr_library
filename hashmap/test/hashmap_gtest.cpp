#include <gtest/gtest.h>
#include <string.h>
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
    exit_code_t ret_val = hash_insert("15", temp, h_table);
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
    hash_insert("15", temp, h_table);
    hash_insert("22", temp, h_table);
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
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    display(h_table);
    exit_code_t ret_val = hash_table_destroy(h_table);
    EXPECT_EQ(ret_val, E_SUCCESS);
}

TEST(BaseTest, Insert_Five_remove_one)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    const char *key = "America";
    exit_code_t ret_val = hash_remove(h_table, key);
    EXPECT_EQ(ret_val, E_SUCCESS);
    display(h_table);
    hash_table_destroy(h_table);
}

TEST(BaseTest, Insert_Five_remove_one_twice)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    const char *key = "America";
    hash_remove(h_table, key);
    exit_code_t ret_val = hash_remove(h_table, key);
    EXPECT_EQ(ret_val, E_KEY_NOT_FOUND);
    hash_table_destroy(h_table);
}

TEST(BaseTest, Insert_Five_remove_one_overflow)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    const char *key = "Hello";
    exit_code_t ret_val = hash_remove(h_table, key);
    EXPECT_EQ(ret_val, E_SUCCESS);
    display(h_table);
    hash_table_destroy(h_table);
}

TEST(BaseTest, Insert_Five_remove_null)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    exit_code_t ret_val = hash_remove(h_table, NULL);
    EXPECT_EQ(ret_val, E_NULL_POINTER);
    display(h_table);
    hash_table_destroy(h_table);
}

TEST(BaseTest, Remove_key_not_found)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    const char *key = "This is not a key";
    exit_code_t ret_val = hash_remove(h_table, key);
    EXPECT_EQ(ret_val, E_KEY_NOT_FOUND);
    display(h_table);
    hash_table_destroy(h_table);
}
TEST(BaseTest, Insert_Five_search)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    void *value = hash_search(h_table, "America");
    EXPECT_EQ(strcmp((const char *)value, words), 0);
    hash_table_destroy(h_table);
}
TEST(BaseTest, Insert_Five_search_null)
{
    const char *words = "This is a test";
    void *temp = (void *)words;
    hash_table_t *h_table = hash_table_init(20, NULL, print_string);
    hash_insert("15", temp, h_table);
    hash_insert("Hello", temp, h_table);
    hash_insert("22", temp, h_table);
    hash_insert("America", temp, h_table);
    hash_insert("99", temp, h_table);
    EXPECT_EQ(h_table->items_in_table, 5);
    void *value = hash_search(h_table, NULL);
    EXPECT_EQ(value, nullptr);
    hash_table_destroy(h_table);
}