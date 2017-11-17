
# Example 1
add_executable(example1 examples/example1/main.cpp)
target_link_libraries(example1 stdc++fs)
target_link_libraries(example1 -pthread)
target_link_libraries(example1 elephantlogger)
add_custom_target(e1 example1)

# Example 2
file(GLOB_RECURSE srcE2 examples/example2/*.cpp)
add_executable(example2 ${srcE2})
target_link_libraries(example2 stdc++fs)
target_link_libraries(example2 -pthread)
target_link_libraries(example2 elephantlogger)
add_custom_target(e2 example2)
