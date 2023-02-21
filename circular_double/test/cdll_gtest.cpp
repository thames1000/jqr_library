#include <gtest/gtest.h>
#include <cdll.h>

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

typedef struct person_ {
        uint32_t age;
        char * name;
    } person_t;

void (*null_func)(void*) = NULL;

void person_free(void * person)
{
    free(((person_t*)person)->name);
    free(person);
}

int comp_int(void * num1, void *num2)
{
    int n1 = *(int*) num1;
    int n2 = *(int*) num2;
    return (n1-n2);
}

void print_int(void * data)
{
    int number = *(int*) data;
    printf("%d", number);
}

int compare_people(void * person1, void *person2)
{
    person_t * p1 = (person_t *) person1;
    person_t * p2 = (person_t *) person2;
    uint32_t first = p1->age;
    uint32_t second = p2->age;
    return (first-second);
}

void print_person(void* person)
{
    person_t * temp = (person_t *) person;
    printf("%s is %d Years old\n", temp->name, temp->age);
}

TEST(BaseTest, Initialize_and_Destroy_Func)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    EXPECT_NE(my_list, nullptr);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_Head_No_List_test)
{
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    int err_code = push_head(nullptr, temp);
    EXPECT_EQ(err_code, -1);
}

TEST(BaseTest, Push_Pop_Head_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    push_head(my_list, temp);
    EXPECT_NE(pop_head(my_list), nullptr);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_Head_Next_Tail_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    push_head(my_list, temp);
    EXPECT_EQ(my_list->head->prev, my_list->tail);
    EXPECT_EQ(my_list->head->next, my_list->tail);
    EXPECT_EQ(my_list->head->prev, my_list->head);
    EXPECT_EQ(my_list->head->next, my_list->head);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_Position_0_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    int err_chk = push_position(my_list, temp, 0);
    EXPECT_EQ(err_chk, -1);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_Position_1_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    push_position(my_list, temp, 1);
    EXPECT_NE(pop_tail(my_list), nullptr);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_Tail_Pop_Head_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff; 
    push_tail(my_list, temp);
    EXPECT_NE(pop_head(my_list), nullptr);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_Tail_Pop_Tail_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    push_tail(my_list, temp);
    list_node_t *rtn_node = pop_tail(my_list);
    EXPECT_NE(rtn_node, nullptr);
    person_free(rtn_node->data);
    free(rtn_node);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_2_Pop_Tail_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    person_t * temp2 = (person_t *)calloc(1, sizeof(person_t));
    temp2->age = 30;
    char* buff2 = (char*) calloc(5,1);
    snprintf(buff2, 5, "Jack");
    temp2->name = buff2;
    push_head(my_list, temp);
    push_head(my_list, temp2);
    list_node_t *rtn_node = pop_tail(my_list);
    person_t *temp_data = (person_t*)rtn_node->data;
    EXPECT_EQ(temp_data->age, 27);
    person_free(rtn_node->data);
    free(rtn_node);
    destroy_list(&my_list);
}

TEST(BaseTest, Push_position_6)
{
    int num_1 = 90;
    int num_2 = 75;
    int num_3 = 60;
    int num_4 = 45;
    int num_5 = 30;
    int num_6 = 15;

    linked_list_t * my_list = create_list(NULL, comp_int, print_int);
    push_head(my_list, &num_6);
    push_head(my_list, &num_5);
    push_head(my_list, &num_4);
    push_head(my_list, &num_3);
    push_head(my_list, &num_2);
    push_head(my_list, &num_1);
    printf("\nBEFORE\n");
    print_list(my_list);

    int num_7 = 20;

    push_position(my_list, &num_7, 6);
    
    printf("\nAFTER\n");
    print_list(my_list);
    void * data = NULL;
    peek_position(my_list, &data, 6);
    EXPECT_EQ(*((int *) data), 20);
}


TEST(BaseTest, bubble_sort)
{
    int num_1 = 90;
    int num_2 = 75;
    int num_3 = 60;
    int num_4 = 45;
    int num_5 = 30;
    int num_6 = 15;

    linked_list_t * my_list = create_list(NULL, comp_int, print_int);
    push_head(my_list, &num_6);
    push_head(my_list, &num_5);
    push_head(my_list, &num_4);
    push_head(my_list, &num_3);
    push_head(my_list, &num_2);
    push_head(my_list, &num_1);
    printf("\nBEFORE\n");
    print_list(my_list);

    bubble_sort(my_list);
    printf("\nAFTER\n");
    print_list(my_list);
    EXPECT_EQ(*(int*) my_list->head->data, 15);
}

TEST(BaseTest, selection_sort)
{
    int num_1 = 90;
    int num_2 = 75;
    int num_3 = 60;
    int num_4 = 45;
    int num_5 = 30;
    int num_6 = 15;

    linked_list_t * my_list = create_list(NULL, comp_int, print_int);
    push_head(my_list, &num_6);
    push_head(my_list, &num_5);
    push_head(my_list, &num_4);
    push_head(my_list, &num_3);
    push_head(my_list, &num_2);
    push_head(my_list, &num_1);
    printf("\nBEFORE\n");
    print_list(my_list);

    selection_sort(my_list);
    printf("\nAFTER\n");
    print_list(my_list);
    EXPECT_EQ(*(int*) my_list->head->data, 15);
}

TEST(BaseTest, insertion_sort)
{
    int num_1 = 90;
    int num_2 = 75;
    int num_3 = 60;
    int num_4 = 45;
    int num_5 = 30;
    int num_6 = 15;

    linked_list_t * my_list = create_list(NULL, comp_int, print_int);
    push_head(my_list, &num_6);
    push_head(my_list, &num_5);
    push_head(my_list, &num_4);
    push_head(my_list, &num_3);
    push_head(my_list, &num_2);
    push_head(my_list, &num_1);
    printf("\nBEFORE\n");
    print_list(my_list);

    insertion_sort(my_list);
    printf("\nAFTER\n");
    print_list(my_list);
    EXPECT_EQ(*(int*) my_list->head->data, 15);
}