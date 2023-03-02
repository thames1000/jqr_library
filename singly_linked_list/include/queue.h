#ifndef QUEUE_H_
#define QUEUE_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include <singly_linked_list.h>

    typedef list_node_t queue_node_t;
    typedef linked_list_t queue_t;

    /**
     * @brief
     *
     * @param free_func
     * @param compare_func
     * @param print_func
     * @return queue_t*
     */
    queue_t *queue_init(void (*free_func)(void *),
                        int (*compare_func)(void *, void *),
                        void (*print_func)(void *));

    /**
     * @brief
     *
     * @param my_queue
     * @param queue_size
     * @return int
     */
    unsigned int size_of_queue(queue_t *my_queue);

    /**
     * @brief
     *
     * @param queue
     */
    void queue_destroy(queue_t *queue);

    /**
     * @brief
     *
     * @param queue
     * @return void*
     */
    void *queue_peek(queue_t *queue);

    /**
     * @brief
     *
     * @param queue
     * @param index
     * @return void*
     */
    void *queue_nth_peek(queue_t *queue, unsigned int index);

    /**
     * @brief
     *
     * @param queue
     * @param data
     */
    void enqueue(queue_t *queue, void *data);

    /**
     * @brief
     *
     * @param queue
     * @return void*
     */
    void *dequeue(queue_t *queue);

    /**
     * @brief
     *
     * @param queue
     */
    void queue_dump(queue_t *queue);

    /**
     * @brief
     *
     * @param my_list
     */
    void reset_tail(queue_t *my_list);

    /**
     * @brief
     *
     * @param node1
     * @param node2
     */
    void swap_nodes(queue_node_t **node1, queue_node_t **node2);

    /**
     * @brief
     *
     * @param my_list
     */
    void bubble_sort(queue_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void selection_sort(queue_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void bubble_sort_swap_nodes(queue_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void selection_sort_node_swap(queue_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     * @return int
     */
    int check_sorted(queue_t *my_list);

    /**
     * @brief
     *
     * @param my_list
     */
    void insertion_sort(queue_t *my_list);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // QUEUE_H_
