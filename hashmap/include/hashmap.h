#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "exit_codes.h"
    typedef struct hash_table hash_table_t;

    /**
     * @brief Initialization function for hash_table_t
     *
     * @param size max size for the hash_table
     * @param free_func method of freeing items in the hash_table (if no free necessary, use NULL)
     * @param print_func method of printing items in the hash_table (if no print needed, use NULL)
     * @return hash_table_t* object pointer to hash_table_t
     */
    hash_table_t *hash_table_init(uint64_t size, void (*free_func)(void *), void (*print_func)(void *));

    /**
     * @brief Destroy function for hash_table_t object
     *
     * @param h_table hash_table_t object pointer to be destroyed
     * @return exit_code_t - E_SUCCESS on clean destroy, E_NULL_POINTER if pointer object passed is NULL
     */
    exit_code_t hash_table_destroy(hash_table_t *h_table);

    /**
     * @brief Function to insert objects into the hash_table_t object
     *
     * @param h_table hash_table_t object to house the key value pair
     * @param key a NULL-terminated const char* to be used for lookup
     * @param value any pointer containing data to be added to the hash_table_t
     * @return exit_code_t E_SUCCESS on successful insertion, E_NULL_POINTER if h_table, key, or value is NULL
     */
    exit_code_t hash_insert(hash_table_t *h_table, const char *key, void *value);

    /**
     * @brief Internal function to allow for printing whats is currently in the hash table
     *
     * @param h_table hash_table_t object pointer that you would like displayed
     */
    void display(const hash_table_t *h_table);

    /**
     * @brief a lookup method of getting the value based on a key
     *
     * @param h_table hash_table_t to lookup information in
     * @param key a NULL-terminated const char* used for lookup
     * @return void* value associated with the key
     */
    void *hash_search(const hash_table_t *h_table, const char *key);

    /**
     * @brief removes a key value pair from the hash_table_t
     *
     * @param h_table hash_table_t object to remove the key value pair from
     * @param key a NULL-terminated const char* used for lookup and removal
     * @return exit_code_t
     */
    exit_code_t hash_remove(hash_table_t *h_table, const char *key);

#ifdef __cplusplus
}
#endif
#endif