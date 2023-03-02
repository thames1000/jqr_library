#ifndef STACK_H_
#define STACK_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

    typedef list_node_t stack_node_t;
    typedef linked_list_t stack_t;

    /**
     * @brief
     *
     * @param free_func
     * @param compare_func
     * @param print_func
     * @return stack_t*
     */
    stack_t *stack_init(void (*free_func)(void *),
                        int (*compare_func)(void *, void *),
                        void (*print_func)(void *));

    /**
     * @brief
     *
     * @param stack
     */
    void stack_destroy(stack_t *stack);

    /**
     * @brief
     *
     * @param stack
     * @param index
     * @return void*
     */
    void *stack_nth_peek(stack_t *stack, unsigned int index);

    /**
     * @brief
     *
     * @param stack
     * @return void*
     */
    void *stack_peek(stack_t *stack);

    /**
     * @brief
     *
     * @param stack
     * @param data
     */
    void stack_push(stack_t *stack, void *data);

    /**
     * @brief
     *
     * @param stack
     * @return void*
     */
    void *stack_pop(stack_t *stack);

    /**
     * @brief
     *
     * @param stack
     */
    void stack_dump(stack_t *stack);

    /**
     * @brief
     *
     * @param my_list
     */
    void reset_tail(stack_t *my_list);

    /**
     * @brief
     *
     * @param node1
     * @param node2
     */
    void swap_nodes(stack_node_t **node1, stack_node_t **node2);

    /**
     * @brief
     *
     * @param my_list
     */
    void bubble_sort(stack_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void selection_sort(stack_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void bubble_sort_swap_nodes(stack_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void selection_sort_node_swap(stack_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     * @return int
     */
    int check_sorted(stack_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void insertion_sort(stack_t *my_list);

#ifdef __cplusplus
}
#endif
#endif // STACK_H_
