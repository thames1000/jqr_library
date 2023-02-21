add_library(
    singly_linked_list
    SHARED
    singly_linked_list.c
)

add_library(
    stack
    SHARED
    stack.c
    singly_linked_list.c
)

add_library(
    queue
    SHARED
    queue.c
    singly_linked_list.c
)

target_include_directories(
        singly_linked_list
        PUBLIC
        ${PROJECT_SOURCE_DIR}/singly_linked_list/include
)

target_include_directories(
        stack
        PUBLIC
        ${PROJECT_SOURCE_DIR}/singly_linked_list/include
)

target_include_directories(
        queue
        PUBLIC
        ${PROJECT_SOURCE_DIR}/singly_linked_list/include
)
