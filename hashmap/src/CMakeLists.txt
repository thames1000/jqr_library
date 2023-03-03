add_library(
    hashmap
    SHARED
    hashmap.c
    exit_codes.c
)

target_include_directories(
    hashmap
    PUBLIC
    ${PROJECT_SOURCE_DIR}/hashmap/include
)
