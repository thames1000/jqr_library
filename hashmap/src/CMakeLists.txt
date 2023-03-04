add_library(
    hashmap
    SHARED
    hashmap.c
    ${PROJECT_SOURCE_DIR}/exit_codes/src/exit_codes.c
)

target_include_directories(
    hashmap
    PUBLIC
    ${PROJECT_SOURCE_DIR}/hashmap/include
    ${PROJECT_SOURCE_DIR}/exit_codes/include
)
