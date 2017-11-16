
# Example 1
add_executable(example1 examples/example1.cpp)
target_link_libraries(example1 stdc++fs)
target_link_libraries(example1 -pthread)
target_link_libraries(example1 elephantlogger)
add_custom_target(e1 example1)

