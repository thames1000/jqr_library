enable_testing()
include(GoogleTest)

add_executable(
        doubly_linked_gtest
        doubly_linked_gtest.cpp
)
target_link_libraries(
        doubly_linked_gtest
        PUBLIC
        doubly_linked_list
        gtest
        gtest_main
)
target_compile_options(
        doubly_linked_gtest
        PUBLIC
        -Wall
        -Wextra
        -Wpedantic
        -Wformat
        -Wvla
        -Wfloat-equal
        -Werror
)
gtest_discover_tests(doubly_linked_gtest)
