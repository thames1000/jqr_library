#include <singly_linked_list.h>
#include <queue.h>


struct list_node
{
    void * data;
    list_node_t * next;
};

struct linked_list
{
    list_node_t * head;
    list_node_t * tail;
    unsigned int size;
    void (*free_func)(void *);
    int (*compare_func)(void *, void *);
    void (*print_func)(void *);
};
queue_t * queue_init(void (*free_func)(void *),
                    int (*compare_func)(void *, void *),
                    void (*print_func)(void *))
{
    queue_t *queue = create_list(free_func, compare_func, print_func);
    return queue;
}

void queue_destroy(queue_t * queue)
{
    destroy_list(&queue);
}

void * queue_nth_peek(queue_t * queue, unsigned int index)
{
    void * data = NULL;
    int err = peek_position(queue, &data, index);
    if (0 != err)
    {
        data = NULL;
    }
    return data;

}

void * queue_peek(queue_t * queue)
{
    void * data = NULL;
    int err = peek_head(queue, &data);
    if (0 != err)
    {
        data = NULL;
    }
    return data;
}

void enqueue(queue_t * queue, void * data)
{
    push_tail(queue, data);
}

void * dequeue(queue_t * queue)
{
    void * data = NULL;
    queue_node_t *node = pop_head(queue);
    if (NULL != node)
    {
        data = node->data;
        free(node);
    }
    return data;
}

void queue_dump(queue_t * queue)
{
    clear_list(&queue);
}
