cmake_minimum_required(VERSION 2.8.2)
project(elephant-logger)


if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


include(CMake/CompilerFlags.cmake)
include(CMake/CreateLibrary.cmake)

option(BUILD_EXAMPLES "Generate all examples executables" OFF)
if(BUILD_EXAMPLES)
    message(STATUS "Generate examples")
    include(CMake/Examples.cmake)
endif()

