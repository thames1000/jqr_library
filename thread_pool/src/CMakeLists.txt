add_library(
    thread_pool
    SHARED
    thread_pool.c
    ${PROJECT_SOURCE_DIR}/exit_codes/src/exit_codes.c
)

target_include_directories(
    thread_pool
    PUBLIC
    ${PROJECT_SOURCE_DIR}/thread_pool/include
    ${PROJECT_SOURCE_DIR}/singly_linked_list/include
    ${PROJECT_SOURCE_DIR}/exit_codes/include
)
