include_directories("${CMAKE_SOURCE_DIR}/include")


# Example 1
file(GLOB_RECURSE srcFilesE1 src/*.cpp examples/example1.cpp)
add_executable(example1 ${srcFilesE1})
target_link_libraries(example1 stdc++fs)
target_link_libraries(example1 -pthread)
add_custom_target(e1 example1)
