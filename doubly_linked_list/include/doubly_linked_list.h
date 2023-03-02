#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

    // the node
    typedef struct list_node list_node_t;

    // the list itself
    typedef struct linked_list linked_list_t;

    /**
     * @brief Create a new linked list object
     *
     * @return linked_list_t* pointer to the new linked list object
     */

    linked_list_t *create_list(void (*free_func)(void *),
                               int (*compare_func)(void *, void *),
                               void (*print_func)(void *));

    /**
     * @brief Check if the list is empty
     *
     * @param my_list the list object
     * @param list_emtpy boolean, true if empty, false if not
     * @return int, error code: 0 for success, anything else is a failure
     */
    int empty_check(linked_list_t *my_list, bool *list_empty);

    /**
     * @brief Return the number of nodes currently in the list
     *
     * @param my_list the list object
     * @param list_size integer pointer for setting the size to pass back up
     * @return int, error code: 0 for success, anything else is a failure
     */
    int size_of_list(linked_list_t *my_list, unsigned int *list_size);

    /**
     * @brief Create a new node at the head of the list containing the data
     *
     * @param my_list the list object
     * @param data data for the node to contain
     * @return int, error code: 0 for success, anything else is a failure
     */
    int push_head(linked_list_t *my_list, void *data);

    /**
     * @brief Create a new node at the tail of the list containing the data
     *
     * @param my_list the list object
     * @param data data for the node to contain
     * @return int, error code: 0 for success, anything else is a failure
     */
    int push_tail(linked_list_t *my_list, void *data);

    /**
     * @brief Create a new node at X position containing the data
     *
     * @param my_list the list object
     * @param data data for the node to contain
     * @param position place to insert the new node
     * @return int, error code: 0 for success, anything else is a failure
     */
    int push_position(linked_list_t *my_list, void *data, unsigned int position);

    /**
     * @brief Function to see the data stored in the head node, but not remove
     * the node
     *
     * @param my_list the list object
     * @param see_data address for an integer pointer to store the data in the node
     * @return int, error code: 0 for success, anything else is a failure
     */
    int peek_head(linked_list_t *my_list, void **see_data);

    /**
     * @brief Function to see the data stored in the tail node, but not remove
     * the node
     *
     * @param my_list the list object
     * @param see_data address for an integer pointer to store the data in the node
     * @return int, error code: 0 for success, anything else is a failure
     */
    int peek_tail(linked_list_t *my_list, void **see_data);

    /**
     * @brief Function to see the data at X position, but not remove the node
     *
     * @param my_list the list object
     * @param see_data address for an integer pointer to store the data in the node
     * @param position place targeted to see what data it holds
     * @return int, error code: 0 for success, anything else is a failure
     */
    int peek_position(linked_list_t *my_list, void **see_data,
                      unsigned int position);

    /**
     * @brief Pops the head node off the list and returns it
     *
     * @param my_list the list obejct
     * @return list_node_t node object if head exists, NULL otherwise
     */
    list_node_t *pop_head(linked_list_t *my_list);

    /**
     * @brief Pops the tail node off the list and returns it
     *
     * @param my_list the list object
     * @return list_node_t node object if tail exists, NULL otherwise
     */
    list_node_t *pop_tail(linked_list_t *my_list);

    /**
     * @brief Pops the node at position X and returns it
     *
     * @param my_list the list object
     * @return list_node_t node object if position exists, NULL otherwise
     */
    list_node_t *pop_position(linked_list_t *my_list, unsigned int position);

    /**
     * @brief Delete the node at the head of the list
     *
     * @param my_list the list object
     * @return int, error code: 0 for success, anything else is a failure
     */
    int remove_head(linked_list_t *my_list);

    /**
     * @brief Delete the node at the tail of the list
     *
     * @param my_list the list object
     * @return int, error code: 0 for success, anything else is a failure
     */
    int remove_tail(linked_list_t *my_list);

    /**
     * @brief Delete the node at X position
     *
     * @param my_list the list object
     * @param position place targeted for deletion
     * @return int, error code: 0 for success, anything else is a failure
     */
    int remove_position(linked_list_t *my_list, unsigned int position);

    /**
     * @brief Function to print the data inside the linked list
     *
     * @param my_list the list object
     */
    void print_list(linked_list_t *my_list);

    /**
     * @brief Clear the nodes, but do not destroy the container
     *
     * @param my_list the list object
     */
    void clear_list(linked_list_t **my_list);

    /**
     * @brief Destroy the linked list
     *
     * @param my_list address of the linked list object to destroy
     */
    void destroy_list(linked_list_t **my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void reset_tail(linked_list_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void bubble_sort(linked_list_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void selection_sort(linked_list_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void bubble_sort_swap_nodes(linked_list_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void selection_sort_node_swap(linked_list_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     * @return int
     */
    int check_sorted(linked_list_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void insertion_sort(linked_list_t *my_list);

#ifdef __cplusplus
}
#endif

#endif