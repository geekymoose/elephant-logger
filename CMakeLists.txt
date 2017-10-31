cmake_minimum_required(VERSION 2.8.2)
project(elephant-logger)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()

# Dependencies
include(CMake/Dependencies.cmake)
include(CMake/CompilerFlags.cmake)

# Executable
include_directories("${CMAKE_SOURCE_DIR}/include")


# Example 1
file(GLOB_RECURSE srcFilesE1 src/*.cpp examples/example1.cpp)
add_executable(example1 ${srcFilesE1})
target_link_libraries(example1 stdc++fs)
add_custom_target(e1 example1)
