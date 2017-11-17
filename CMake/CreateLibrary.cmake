include_directories("${CMAKE_SOURCE_DIR}/include")


# Lib Elephant Logger
file(GLOB_RECURSE srcFiles src/*.cpp)
add_library(elephantlogger STATIC ${srcFiles})

target_link_libraries(elephantlogger
    stdc++fs
    pthread)

