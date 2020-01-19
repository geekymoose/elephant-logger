include_directories("${CMAKE_SOURCE_DIR}/include")


# Example 1
add_executable(example1 ex1_simpleUse/main.cpp)
target_link_libraries(example1 -pthread)
add_custom_target(runExample1 example1)

# Example 2
file(GLOB_RECURSE srcE2 ex2_multiClasses/*.cpp)
add_executable(example2 ${srcE2})
target_link_libraries(example2 -pthread)
add_custom_target(runExample2 example2)

# Example 3
add_executable(example3 ex3_customOutputs/main.cpp)
target_link_libraries(example3 -pthread)
add_custom_target(runExample3 example3)
