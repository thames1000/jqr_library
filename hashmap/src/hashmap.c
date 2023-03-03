#include <stdio.h>
#include <stdint.h>
#include "exit_codes.h"
#include "hashmap.h"

// Values needed for FNV-1 Hash
#define FNV_PRIME 0x100000001b3
#define FNV_OFFSET 0xcbf29ce484222325

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
    void (*free_func)(void *);
} hash_table_t;

/**
  EXAMPLE PSUEDOCODE FOR HASH ALGORITHM
    hash := FNV_OFFSET

    for each byte_of_data to be hashed do
        hash := hash × FNV_PRIME
        hash := hash XOR byte_of_data

    return hash
*/
// Modified from code found at below location
// SOURCE: https://www.programmingalgorithms.com/algorithm/fnv-hash/c/
uint64_t FNVHash(void *data, uint64_t length)
{
    uint64_t hash = FNV_OFFSET;
    uint64_t i = 0;
    unsigned char *str = (unsigned char *)data;
    for (i = 0; i < length; str++, i++)
    {
        hash *= FNV_PRIME;
        hash ^= (*str);
    }
    return hash;
}
uint64_t get_index(void *data, uint64_t size, hash_table_t *h_table)
{
    if (NULL == data)
    {
        return size + 1;
    }
    uint64_t hash = FNVHash(data, size);
    return (hash % h_table->max_size);
}

data_point_t *make_data_point(void *data)
{
    data_point_t *ret_data_point = (data_point_t *)calloc(1, sizeof(*ret_data_point));
    if (NULL == ret_data_point)
    {
        return NULL;
    }
    ret_data_point->data = data;
    ret_data_point->overflow = NULL;
    return ret_data_point;
}

exit_code_t hash_insert(void *data, uint32_t size, hash_table_t *h_table)
{
    if (NULL == data)
    {
        return E_NULL_POINTER;
    }
    uint32_t idx = get_index(data, size, h_table);
    data_point_t *value = make_data_point(data);
    if (NULL == value)
    {
        return E_NULL_POINTER;
    }
    if (NULL == h_table->table[idx])
    {
        h_table->table[idx] = value;
    }
    else
    {
        data_point_t *temp = h_table->table[idx];
        while (NULL != temp->overflow)
        {
            temp = temp->overflow;
        }
        temp->overflow = value;
    }
    return E_SUCCESS;
}

// void *hash_search(void *data)
// {
// }

// void hash_remove(void *data)
// {
// }

hash_table_t *hash_table_init(uint64_t size, void (*free_func)(void *))
{
    if (0 == size)
    {
        return NULL;
    }
    hash_table_t *h_table = (hash_table_t *)calloc(1, sizeof(*h_table));
    if (NULL == h_table)
    {
        return NULL;
    }
    h_table->table = (data_point_t **)calloc(size, sizeof(data_point_t *));
    if (NULL == h_table->table)
    {
        free(h_table);
        return NULL;
    }
    // Explicitly setting each index in the table to NULL
    for (int index = 0; index < size; index++)
    {
        h_table->table[index] = NULL;
    }
    h_table->free_func = free_func;
    h_table->max_size = size;
    h_table->spots_used = 0;
    return h_table;
}

void clear_overflow(data_point_t *data, void (*free_func)(void *))
{
    if (NULL == data)
    {
        return;
    }
    if (NULL != data->overflow)
    {
        clear_overflow(data->overflow, free_func);
    }
    if (NULL != free_func)
    {
        free_func(data->data);
    }
    free(data);
}

exit_code_t hash_table_destroy(hash_table_t *h_table)
{
    if (NULL == h_table)
    {
        return E_NULL_POINTER;
    }
    for (int idx = 0; idx < h_table->max_size; idx++)
    {
        clear_overflow(h_table->table[idx], h_table->free_func);
    }
    free(h_table->table);
    free(h_table);
    return E_SUCCESS;
}