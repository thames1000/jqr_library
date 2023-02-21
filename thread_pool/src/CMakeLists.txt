add_library(
    thread_pool
    SHARED
    thread_pool.c
    exit_codes.c
)

target_include_directories(
        thread_pool
        PUBLIC
        ${PROJECT_SOURCE_DIR}/thread_pool/include
)
