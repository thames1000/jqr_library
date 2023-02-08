#include <gtest/gtest.h>
#include <linked_list.h>

struct list_node
{
    void * data;
    list_node_t * next;
    list_node_t * prev;
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

TEST(BaseTest, Push_Head_Pop_Tail_test)
{
    linked_list_t * my_list = create_list(person_free, compare_people, print_person);
    person_t * temp = (person_t *)calloc(1, sizeof(person_t));
    temp->age = 27;
    char* buff = (char*) calloc(7,1);
    snprintf(buff, 7, "Thames");
    temp->name = buff;
    push_head(my_list, temp);
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


// TEST(BaseTest, Pop_test)
// {
//     stack_adt_t * stack = stack_init(20, free);
//     char buff[30];
//     for (int index = 0; index < 25; index++) // Does not push if stack is full
//     {
//         snprintf(buff, 30, "Hello world: %d\n", index);
//         stack_push(stack, strdup(buff));
//     }
//     void * tester = stack_pop(stack);
//     EXPECT_NE(tester, nullptr);
//     free(tester);
//     stack_destroy(stack);
// }

// TEST(BaseTest, Dump_and_pop_test)
// {
//     stack_adt_t * stack = stack_init(20, free);
//     char buff[30];
//     for (int index = 0; index < 25; index++)
//     {
//         snprintf(buff, 30, "Hello world: %d\n", index);
//         stack_push(stack, strdup(buff));
//     }
//     stack_dump(stack);
//     EXPECT_EQ(stack_pop(stack), nullptr);
//     stack_destroy(stack);
// }

// TEST(BaseTest, struct_object_push_and_destroy)
// {
//     stack_adt_t * stack = stack_init(20, person_free);
//     EXPECT_NE(stack, nullptr);
    
//     for (int index = 0; index < 15; index++)
//     {
//         person_t * person = (person_t*) calloc(1,sizeof(person_t));
//         person->age=index;
//         person->name=strdup("My Name");
//         stack_push(stack, person);
//     }
//     stack_destroy(stack);
// }