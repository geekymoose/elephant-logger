include_directories("${CMAKE_SOURCE_DIR}/include")


# Example 1
add_executable(example1 ex1_simpleUse/main.cpp)
add_custom_target(runExample1 example1)

# Example 2
file(GLOB_RECURSE srcEx2 ex2_multiClasses/*.cpp)
add_executable(example2 ${srcEx2})
add_custom_target(runExample2 example2)

# Example 3
add_executable(example3 ex3_customOutputs/main.cpp)
add_custom_target(runExample3 example3)

# Example 4
add_executable(example4 ex4_loggerCategoriesFilter/main.cpp)
add_custom_target(runExample4 example4)

