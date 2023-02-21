#ifndef STACK_H_
#define STACK_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

typedef list_node_t stack_node_t;
typedef linked_list_t stack_t;
stack_t * stack_init(void (*free_func)(void *),
                    int (*compare_func)(void *, void *),
                    void (*print_func)(void *));
void stack_destroy(stack_t * stack);
void * stack_nth_peek(stack_t * stack, unsigned int index);
void * stack_peek(stack_t * stack);
void stack_push(stack_t * stack, void * data);
void * stack_pop(stack_t * stack);
void stack_dump(stack_t * stack);

#ifdef __cplusplus
}
#endif
#endif // STACK_H_
