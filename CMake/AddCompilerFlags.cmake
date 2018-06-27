message(STATUS "Detected Operating SYstem: ${CMAKE_SYSTEM_NAME}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No BUILD_TYPE set: uses Release")
    message(STATUS "Build types: Debug / Release")
    set(CMAKE_BUILD_TYPE Release)
endif()
