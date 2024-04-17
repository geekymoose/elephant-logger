cmake_minimum_required(VERSION 3.5.0)
project(elephant-logger)


if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. You should create a 'build' directory then cmake from there. `mkdir build && cd build`")
endif()


# ------------------------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------------------------
message(STATUS "Detected Operating System: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No BUILD_TYPE set: uses Release")
    message(STATUS "Available build types: Debug Release RelWithDebInfo MinSizeRel")
    set(CMAKE_BUILD_TYPE Release)
else()
    message(STATUS "BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif(NOT CMAKE_BUILD_TYPE)


# ------------------------------------------------------------------------------
# Utils
# ------------------------------------------------------------------------------

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)


# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------
option(elephant_examples "Generate all examples" OFF)
if(elephant_examples)
    message(STATUS "Generate examples")
    add_subdirectory("examples")
endif()

