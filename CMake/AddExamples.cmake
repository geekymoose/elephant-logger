include_directories("${CMAKE_SOURCE_DIR}/include")


# Example 1
add_executable(example1 examples/ex1_simpleUse/main.cpp)
target_link_libraries(example1 -pthread)
target_link_libraries(example1 elephantlogger)
add_custom_target(runExample1 example1)

# Example 2
file(GLOB_RECURSE srcE2 examples/ex2_multiClasses/*.cpp)
add_executable(example2 ${srcE2})
target_link_libraries(example2 -pthread)
target_link_libraries(example2 elephantlogger)
add_custom_target(runExample2 example2)

# Example 3
add_executable(example3 examples/ex3_saveLogs/main.cpp)
target_link_libraries(example3 -pthread)
target_link_libraries(example3 elephantlogger)
add_custom_target(runExample3 example3)

# Example 4
add_executable(example4 examples/ex4_customInit/main.cpp)
target_link_libraries(example4 -pthread)
target_link_libraries(example4 elephantlogger)
add_custom_target(runExample4 example4)
