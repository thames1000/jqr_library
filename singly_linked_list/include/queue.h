#ifndef STACK_H_
#define STACK_H_

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>


typedef list_node_t queue_node_t;
typedef linked_list_t queue_t;

queue_t * queue_init(void (*free_func)(void *),
                    int (*compare_func)(void *, void *),
                    void (*print_func)(void *));
void queue_destroy(queue_t * queue);
void * queue_peek(queue_t * queue);
void * queue_nth_peek(queue_t * queue, unsigned int index);
void enqueue(queue_t * queue, void * data);
void * dequeue(queue_t * queue);
void queue_dump(queue_t * queue);

#ifdef __cplusplus
}
#endif
#endif // STACK_H_
