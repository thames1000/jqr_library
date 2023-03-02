#include <singly_linked_list.h>
#include <stack.h>

struct list_node
{
    void *data;
    list_node_t *next;
};

struct linked_list
{
    list_node_t *head;
    list_node_t *tail;
    unsigned int size;
    void (*free_func)(void *);
    int (*compare_func)(void *, void *);
    void (*print_func)(void *);
};

stack_t *stack_init(void (*free_func)(void *),
                    int (*compare_func)(void *, void *),
                    void (*print_func)(void *))
{
    stack_t *my_stack = create_list(free_func, compare_func, print_func);
    return my_stack;
}

void stack_destroy(stack_t *stack)
{
    destroy_list(&stack);
}

void *stack_nth_peek(stack_t *stack, unsigned int index)
{
    void *data = NULL;
    int err = peek_position(stack, &data, index);
    if (0 != err)
    {
        data = NULL;
    }
    return data;
}

void *stack_peek(stack_t *stack)
{
    void *data = NULL;
    int err = peek_head(stack, &data);
    if (0 != err)
    {
        data = NULL;
    }
    return data;
}

void stack_push(stack_t *stack, void *data)
{
    push_head(stack, data);
}

void *stack_pop(stack_t *stack)
{
    void *data = NULL;
    stack_node_t *node = pop_head(stack);
    if (NULL != node)
    {
        data = node->data;
        free(node);
    }
    return data;
}

void stack_dump(stack_t *stack)
{
    clear_list(&stack);
}
