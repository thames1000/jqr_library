add_library(
    cdll
    SHARED
    circ_doub_linked_list.c
)

target_include_directories(
        cdll
        PUBLIC
        ${PROJECT_SOURCE_DIR}/circular_double/include
)
