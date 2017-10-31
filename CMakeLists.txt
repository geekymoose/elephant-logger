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
add_executable(elephant-logger src/main.cpp)
add_custom_target(run elephant-logger)
