#include "linked_list.h"

struct list_node
{
    void * data;
    list_node_t * next;
    list_node_t * prev;
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

linked_list_t * create_list(void (*free_func)(void *),
                    int (*compare_func)(void *, void *),
                    void (*print_func)(void *))
{
    linked_list_t * rtn_list = calloc(1, sizeof(linked_list_t));
    if (NULL != rtn_list)
    {
        rtn_list->head = NULL;
        rtn_list->tail = NULL;
        rtn_list->size = 0;
        if (NULL == free_func)
        {
            rtn_list->free_func = NULL;
        }
        else
        {
            rtn_list->free_func = free_func;
        }
        rtn_list->compare_func=compare_func;
        rtn_list->print_func=print_func;
    }
    return rtn_list;
}

int empty_check(linked_list_t * my_list, bool * list_empty)
{
    int err_check = -1;

    if ((NULL == list_empty) || (NULL == my_list))
    {
        return err_check;
    }
    err_check = 0;
    *list_empty = (NULL == my_list->head && 0 == my_list->size);

    return err_check;
}

int size_of_list(linked_list_t * my_list, unsigned int * list_size)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (NULL == list_size || -1 == err_check)
    {
        err_check = -1;
    }
    else
    {
        *list_size = my_list->size;
    }
    return err_check;
}

list_node_t * create_node(void * data)
{
    list_node_t * new_node = calloc(1, sizeof(list_node_t));
    if (NULL == new_node)
    {
        goto END;
    }
    new_node->data = data;
    new_node->next = NULL;
    
END:
    return new_node;
}

//******************************************************************************
// ALL THE PUSH FUNCTIONS

int push_head(linked_list_t * my_list, void * data)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (NULL == my_list)
    {
        return err_check;
    }
    err_check = 0;
    list_node_t * new_node = create_node(data);
    if (NULL == my_list->head)
    {
        my_list->head = new_node;
        my_list->tail = new_node;
        my_list->tail->next = my_list->head;
        my_list->head->prev = my_list->tail;
    }
    else
    {
        new_node->next = my_list->tail->next;
        my_list->tail->next = new_node;
        my_list->head = new_node;
    }
    my_list->size++;
    return err_check;
}

int push_tail(linked_list_t * my_list, void * data)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (-1 != err_check)
    {
        list_node_t * new_node = create_node(data);
        if (empty)
        {
            new_node->next = new_node;
            new_node->prev = new_node;
            my_list->head = new_node;
            my_list->tail = new_node;
        }
        else
        {
            new_node->prev = my_list->tail;
            new_node->next = my_list->head;
            my_list->tail->next = new_node;
            my_list->tail = new_node;
        }
        my_list->size++;
    }
    return err_check;
}

int push_position(linked_list_t * my_list, void * data, unsigned int position)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if ((-1 == err_check) || (0 == position))
    {
        err_check = -1;
    }
    else if (1 == position)
    {
        push_head(my_list, data);
    }
    else
    {
        list_node_t * new_node = create_node(data);
        unsigned int size = 0;
        unsigned int index = 2;
        list_node_t * node = my_list->head;
        err_check = size_of_list(my_list, &size);
        if ((-1 == err_check) || (size + 1 < position))
        {
            err_check = -1;
            if (NULL != my_list->free_func)
                my_list->free_func(new_node->data);
            free(new_node);
            goto END;
        }
        else if (size + 1 == position)
        {
            push_tail(my_list, data);
            goto END;
        }

        while (position > index)
        {
            node = node->next;
            index++;
        }
        list_node_t * temp_node = node->next;
        node->next = new_node;
        new_node->data = data;
        new_node->next = temp_node;
        new_node->prev = node;
        temp_node->prev = new_node;
        
        my_list->size++;
    }
END:
    return err_check;
}

//******************************************************************************
// ALL THE PEEK FUNCTIONS

int peek_head(linked_list_t * my_list, void ** see_data)
{
    int err_check = -1;
    if ((NULL == my_list) || (NULL == see_data))
    {
        return err_check;
    }
    if (NULL != my_list->head)
    {
        err_check = 0;
        *see_data = my_list->head->data;
    }
    return err_check;
}

int peek_tail(linked_list_t * my_list, void ** see_data)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if ((NULL == see_data) || empty)
    {
        err_check = -1;
    }
    else
    {
        *see_data = my_list->tail->data;
    }
    return err_check;
}

int peek_position(linked_list_t * my_list, void ** see_data,
                  unsigned int position)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if ((NULL == see_data) || empty || (0 == position) || (-1 == err_check))
    {
        err_check = -1;
    }
    else
    {
        unsigned int size = 0;
        unsigned int index = 1;
        list_node_t * node = my_list->head;
        err_check = size_of_list(my_list, &size);
        if ((-1 == err_check) || ((size + 1) < position))
        {
            err_check = -1;
            return err_check;
        }
        while (position != index)
        {
            node = node->next;
            index++;
        }
        *see_data = node->data;
    }
    return err_check;
}

//******************************************************************************
// ALL THE POP FUNCTIONS

list_node_t * pop_head(linked_list_t * my_list)
{
    list_node_t * rtn_node = NULL;
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (!empty && (-1 != err_check)) // if linked list is not empty and not NULL
    {
        if (1 == my_list->size)
        {
            my_list->tail = NULL;
        }
        rtn_node = my_list->head;
        my_list->head = my_list->head->next;
        rtn_node->next = NULL;
        if (NULL != my_list->head)
        {
            my_list->head->prev = NULL;
        }
        my_list->size--;
    }
    return rtn_node;
}

list_node_t * pop_tail(linked_list_t * my_list)
{
    list_node_t * rtn_node = NULL;
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (!empty && (-1 != err_check)) // if linked list is not empty and not NULL
    {
        if (1 == my_list->size)
        {
            my_list->head = NULL;
        }
        rtn_node = my_list->tail;
        my_list->tail = my_list->tail->prev;
        if (NULL != my_list->tail)
        {
            my_list->tail->next = NULL;
        }
        my_list->size--;
    }
    return rtn_node;
}

list_node_t * pop_position(linked_list_t * my_list, unsigned int position)
{
    list_node_t * del_node = NULL;
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (empty || (0 == position) || (-1 == err_check))
    {
        return NULL;
    }
    else
    {
        unsigned int size = 0;
        unsigned int index = 2;
        del_node = my_list->head;
        list_node_t * node = del_node->next;
        err_check = size_of_list(my_list, &size);
        if ((-1 == err_check) || (position > size))
        {
            return NULL;
        }
        if (1 == position)
        {
            my_list->head = node;
            my_list->size--;
            return del_node;
        }
        else
        {
            while (position > index)
            {
                del_node = node;
                node = node->next;
                index++;
            }
            del_node->next = node->next;
            my_list->size--;
            if (position == size)
            {
                my_list->tail = del_node;
                my_list->tail->next = NULL;
            }
            return node;
        }
    }

    return del_node;
}

//******************************************************************************
// ALL THE REMOVE FUNCTIONS

int remove_head(linked_list_t * my_list)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (-1 == err_check) // if linked list is not empty and not NULL
    {
        return err_check;
    }
    else if (empty)
    {
        err_check = -1;
    }
    else
    {
        list_node_t * node = pop_head(my_list);
        if (NULL != my_list->free_func)
            my_list->free_func(node->data);
        free(node);
    }
    return err_check;
}

int remove_tail(linked_list_t * my_list)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (-1 == err_check || empty)
    {
        err_check = -1;
    }
    else
    {
        list_node_t * node = pop_tail(my_list);
        if (NULL != my_list->free_func)
            my_list->free_func(node->data);
        free(node);
    }
    return err_check;
}

int remove_position(linked_list_t * my_list, unsigned int position)
{
    list_node_t * del_node = NULL;
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    if (empty || (0 == position) || (-1 == err_check))
    {
        err_check = -1;
    }
    else
    {
        del_node = pop_position(my_list, position);
        if (NULL != my_list->free_func)
            my_list->free_func(del_node->data);
        free(del_node);
    }
    return err_check;
}

//******************************************************************************

void print_list(linked_list_t * my_list)
{
    bool empty = true;
    int err_check = empty_check(my_list, &empty);
    int temp_size = my_list->size;
    printf("[");
    if (!empty && -1 != err_check)
    {
        list_node_t * node = my_list->head;
        while (temp_size > 1)
        {
            my_list->print_func(node->data);
            printf(", ");
            node = node->next;
            temp_size--;
        }
        my_list->print_func(node->data);
    }
    printf("]\n");
    return;
}

void clear_list(linked_list_t ** my_list)
{
    if (NULL == my_list || NULL == (*my_list))
    {
        return;
    }

    while ((*my_list)->size > 1)
    {
        list_node_t * temp = (*my_list)->head;

        // free the head node and null it
        (*my_list)->head = (*my_list)->head->next;
        if (NULL != (*my_list)->free_func)
            (*my_list)->free_func(temp->data);
        free(temp);
        temp = NULL;

        // set the next node into the head slot
        (*my_list)->size--;
    }
}

void destroy_list(linked_list_t ** my_list)
{
    if (NULL == my_list)
    {
        return;
    }

    // clear the nodes
    clear_list(my_list);

    // kill the container
    free(*my_list);
    *my_list = NULL;
}

// Bubble Sort
void bubble_sort(linked_list_t * my_list)
{
    list_node_t * temp_node = my_list->head;
    int continuation = 0;
    do
    {
        int response = my_list->compare_func(temp_node->data, temp_node->next->data);
        int swap = (response > 0) ? 1 : 0;
        if (1 == swap)
        {
            swap_nodes(&temp_node, &(temp_node->next));
            continuation = 1;
        }
        temp_node = temp_node->next;
    } while (NULL != temp_node->next);
    if (1 == continuation)
    {
        print_list(my_list);
        bubble_sort(my_list);
    }
    else
    {
        print_list(my_list);
    }
}
void reset_tail(linked_list_t * my_list)
{
    list_node_t * node = my_list->head;
    while (NULL!=node->next)
    {
        node=node->next;
    }
    my_list->tail=node;
}
// Quick Sort
// Insertion Sort
// Merge Sort

// Selection Sort
void selection_sort(linked_list_t * my_list)
{
    list_node_t * start_node = my_list->head;
    unsigned int i, j;
    int result;
    print_list(my_list);
    for (i = 0; i < my_list->size - 1; i++)
    {
        list_node_t * curr_node = start_node->next;
        result = my_list->compare_func(start_node->data, curr_node->data);
        list_node_t * min = (result < 0 ? start_node : curr_node);
        for (j = i + 1; j < my_list->size - 1; j++)
        {
            curr_node = curr_node->next;
            result = my_list->compare_func(curr_node->data, min->data);
            if (result < 0)
            {
                min = curr_node;
            }
        }
        swap_nodes(&min, &start_node);
        start_node = start_node->next;
        print_list(my_list);
    }
}

// swap nodes (for bubble sort and selection sort)
void swap_nodes(list_node_t ** node1, list_node_t ** node2)
{
    void * temp_data = (*node1)->data;
    (*node1)->data = (*node2)->data;
    (*node2)->data = temp_data;
}

void bubble_sort_swap_nodes(linked_list_t * my_list)
{
    unsigned int comparisons = 0;
    unsigned int swaps = 0;
    unsigned int i, j;
    for (i = 0; i < my_list->size; i++)
    {
        int continuation = 0;
        list_node_t * start = my_list->head;
        list_node_t * prev = NULL;
        for (j = 0; j < ((my_list->size) - i - 1); j++)
        {
            list_node_t * p1 = start;
            list_node_t * p2 = start->next;
            int result = my_list->compare_func(p1->data, p2->data);
            comparisons++;
            if (result > 0)
            {
                swaps++;
                continuation = 1;
                if (NULL == prev)
                {
                    my_list->head = p2;
                }
                else
                {
                    prev->next = p2;
                }
                list_node_t * temp = p2->next;
                p2->next = p1;
                p1->next = temp;
            }
            prev = (result > 0) ? p2 : p1;
            start = (result > 0) ? p1 : p2;
        }
        if (0 == continuation)
            break;
        print_list(my_list);
    }
    printf("%u comparisons, %u swaps\n", comparisons, swaps);
}

void selection_sort_node_swap(linked_list_t * my_list)
{
    list_node_t * b4_start = NULL;
    list_node_t * start_node = my_list->head;
    unsigned int i, j;
    int result;
    list_node_t * prev_min=NULL;
    printf("Original:  ");
    print_list(my_list);
    for (i = 0; i < my_list->size - 1; i++)
    {
        list_node_t * b4_min = start_node;
        list_node_t * b4_cur;
        list_node_t * curr_node = start_node->next;
        result = my_list->compare_func(start_node->data, curr_node->data);
        list_node_t * min = (result < 0 ? start_node : curr_node);
        
        for (j = i + 1; j < my_list->size-1; j++)
        {
            b4_cur = curr_node;
            curr_node = curr_node->next;
            result = my_list->compare_func(curr_node->data, min->data);
            if (result < 0)
            {
                b4_min = b4_cur;
                min = curr_node;
            }

        }
        if (start_node == min)
        {
            start_node=start_node->next;
            printf("No swap:   ");
            print_list(my_list);
            prev_min = min;
            if (1==check_sorted(my_list))
            {
                printf("Sorted:    ");
                print_list(my_list);
                reset_tail(my_list);
                return;
            }
            continue;
        }
        if (NULL == b4_start)
        {
            my_list->head = min;
        }
        b4_min->next=start_node;
        list_node_t * temp = start_node->next;
        start_node->next=min->next;
        printf("Swap:      ");
        start_node = temp;  
        b4_start=min;
        b4_start->next=start_node;
        if (NULL!=prev_min)
        {
            prev_min->next = min;
            prev_min=min;
        }
        else if (start_node!=min)
        {
            prev_min = min;
        }
        print_list(my_list);
    }
    printf("Sorted:    ");
    print_list(my_list);
    reset_tail(my_list);
}
int check_sorted(linked_list_t * my_list)
{
    int sorted=1;
    list_node_t * first=my_list->head;
    for (unsigned int i = 0; i < my_list->size - 1; i++)
    {
        list_node_t * second = first->next;
        if (my_list->compare_func(first->data,second->data)>0)
        {
            sorted=0;
            break;
        }
        first=second;
    }
    return sorted;
}

void insertion_sort(linked_list_t * my_list)
{
    list_node_t * last_sorted =  my_list->head;
    list_node_t * curr_node = last_sorted->next;
    list_node_t * temp;
    list_node_t * check_node;
    list_node_t *  prev_check;
    for (unsigned int i = 0; i < my_list->size-1;i++)
    {
        
        int result=my_list->compare_func(last_sorted->data,curr_node->data);
        if (result>0)
        {
            check_node=my_list->head;
            prev_check=NULL;
            do
            {
                if (NULL==prev_check)
                {
                    if(my_list->compare_func(check_node->data,curr_node->data)>0)
                    {
                        temp=curr_node->next;
                        curr_node->next=check_node;
                        last_sorted->next = temp;
                        my_list->head=curr_node;
                        break;
                    }
                    else
                    {
                        prev_check=check_node;
                        check_node=check_node->next;
                    }
                }
                else if (my_list->compare_func(check_node->data,curr_node->data)>0)
                {
                    temp = curr_node->next;
                    prev_check->next=curr_node;
                    curr_node->next=check_node;
                    last_sorted->next=temp;
                    break;
                }
                else
                {
                    prev_check=check_node;
                    check_node=check_node->next;
                }
            }while (my_list->compare_func(prev_check->data,curr_node->data)<0);
            curr_node=last_sorted->next;
        }
        else
        {
            last_sorted=curr_node;
            curr_node=curr_node->next;
        }
        reset_tail(my_list);
        print_list(my_list);
        if (1==check_sorted(my_list))
        {
            printf("Sorted\n");
            return;
        }
    }
}

