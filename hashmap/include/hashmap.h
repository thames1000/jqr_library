#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "exit_codes.h"
    typedef struct hash_table hash_table_t;
    hash_table_t *hash_table_init(uint64_t size, void (*free_func)(void *), void (*print_func)(void *));
    exit_code_t hash_table_destroy(hash_table_t *h_table);
    exit_code_t hash_insert(void *data, uint32_t size, hash_table_t *h_table);
    void display(hash_table_t *h_table);

#ifdef __cplusplus
}
#endif
#endif