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
file(GLOB_RECURSE srcFiles *.cpp)
add_executable(elephant-logger ${srcFiles})
add_custom_target(run elephant-logger)
