cmake_minimum_required(VERSION 3.20)
project(dsa_lib C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps)
add_subdirectory(circular_double)
add_subdirectory(singly_linked_list)
add_subdirectory(doubly_linked_list)
add_subdirectory(thread_pool)
add_subdirectory(hashmap)

# Disable response files
set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES Off)

# add_library(dsa_lib INTERFACE)
# target_link_libraries(dsa_lib INTERFACE hashmap cdll stack queue singly_linked_list doubly_linked_list thread_pool)