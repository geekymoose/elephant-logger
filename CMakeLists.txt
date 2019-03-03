cmake_minimum_required(VERSION 2.8.2)
project(elephant-logger)


if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
    message(FATAL_ERROR "in-source build not allowed. Use another directory.")
endif()


# ------------------------------------------------------------------------------
# Misc
# ------------------------------------------------------------------------------
include("CMake/AddCompilerFlags.cmake")


# ------------------------------------------------------------------------------
# Examples
# ------------------------------------------------------------------------------
option(elephant_examples "Generate all examples" OFF)
if(elephant_examples)
    message(STATUS "Generate examples")
    include("CMake/AddExamples.cmake")
endif()

