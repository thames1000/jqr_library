add_library(
    doubly_linked_list
    SHARED
    doubly_linked_list.c
)

target_include_directories(
        doubly_linked_list
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
