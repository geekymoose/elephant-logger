# Elephant Logger
C++ logger library for multi-threads realtime system with printf like format.

[![release-version](https://img.shields.io/badge/release-beta--version-red.svg)]()
[![build-status](https://travis-ci.org/GeekyMoose/elephant-logger-realtime.svg?branch=master)](https://travis-ci.org/GeekyMoose/elephant-logger-realtime)
[![license](https://img.shields.io/badge/license-Apache-blue.svg)](https://github.com/GeekyMoose/elephant-logger-realtime/blob/dev/LICENSE.txt)

![icon-LittleElephant](https://i.imgur.com/zXS7zHs.png)


> Your code

![screenshot-yourcode](https://i.imgur.com/nhAHD7L.png)

> Execution

![screenshot-result](https://i.imgur.com/cD57rVa.png)





# WARNING

## Work in progress
> Work in progress. Important changes may happen. (And doc may be not uptodate)

## Performance
> My goal is to implement a logger with high performance.
> However, I haven't done profiling and performance test yet!!
> (My solution could be even slower than simple cout: profiling required)





# Overview

## Description
This project is a C++ logger designed for Realtime softwares.
Realtime doesn't mean here that logs are displayed in realtime.
Instead, the goal is that logging shouldn't affect the programme execution time.
(The least we can).
Inside the software thread (Your running programme), logs call only queue the message.
The logger is started on its own thread which then process the logs, print them, write in files etc...

## Features
- Simple logging calls with log levels
    - LOG_WTF
    - LOG_ERROR
    - LOG_WARNING
    - LOG_CONFIG
    - LOG_INFO
    - LOG_TRACE
    - LOG_DEBUG
- Printf like log format
    - Log message works like printf message format.
- Outputs
    - Write logs in several outputs.
        - File
        - Cout
        - Visual Studio Console (Cout is not supported)
- Channels
    - Up to 10 channels
    - Each channel may be binded to several outputs.
- Log configurations
    - Log Level: Bypass all logs with lower critique level.
    - Save: save all logs in file.
    - ClearAtStart: reset log file at start. (Otherwise, append).





# Use the library in your project
## Basics
- Build the logger library (Or download the build if available).
- Add elephant `include` path in your project includes path.
- Add static library in your project dependencies.
- Add `#include <elephantlogger.h>` into your cpp/h files.
- Call `elephant::init()` in your main.
- You're done!





# Build the library

## Dependencies / Requirements
- C++11
- experimental/filesystem support (stdc++fs)
- thread (pthread)
- pragma support (pragma once)


## Build on GNU/Linux with CMake
- [CMake](https://cmake.org/)

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j4
```
> DCMAKE_BUILD_TYPE options: Debug / Release / RelWithDebInfo / MinSizeRel


## Execute examples on GNU/Linux (CMake)
Set CMake option "BUILD_EXAMPLES" to ON (OFF by default)

```
mkdir build
cd build
cmake -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release ..
make -j4
make ex1
```
> DCMAKE_BUILD_TYPE options: Debug / Release / RelWithDebInfo / MinSizeRel

> Start example 1. For other, change '1' by example number.


## Build on Windows
> TODO: Not supported yet.





# Example
> Several examples are available in `examples` directory.

```
#include "elephantlogger.h"

#include <chrono>
#include <thread>


// A simple test
int main(int argc, char** argv) {

    elephant::init();

    LOG_WTF(0, "1. TEST ERROR");
    LOG_ERROR(0, "1. TEST ERROR");
    LOG_WARNING(0, "2. TEST WARNING");
    LOG_CONFIG(0, "3. TEST CONFIG");
    LOG_INFO(0, "4. TEST INFO");
    LOG_TRACE(0, "5. TEST TRACE");
    LOG_DEBUG(0, "6. TEST DEBUG");

    LOG_DEBUG(0, "Integer value: %d", 42);
    LOG_DEBUG(0, "Float value: %f", 31.9);
    LOG_DEBUG(0, "Bool value (true): %d", true);
    LOG_DEBUG(0, "NULL (Using d): %d", NULL);
    LOG_DEBUG(0, "NULL (Using s): %s", NULL);

    LOG_DEBUG(0, "String: %s / Integer: %d / Float: %f / Char: %c", "Hello", 2, 7.1, 'c');

    for(int k = 0; k < 4; ++k) {
        LOG_DEBUG(0, "Log in loop (counter: %d)", k);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    LOG_INFO(0, "See you");
    return 0;
}
```





# Generate Doxygen documentation
- `doxygen Doxyfile`
- Documentation generated in build-doxygen folder.





# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
Logo made by [Marie-Pier Bouffard](https://www.artstation.com/mariepierbouffard)
