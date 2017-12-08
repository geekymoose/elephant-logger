![Elephant-Logger](https://i.imgur.com/vRG1Dsx.png)

[![release-version](https://img.shields.io/badge/release-beta--version-red.svg)]()
[![build-status](https://travis-ci.org/GeekyMoose/elephant-logger-realtime.svg?branch=master)](https://travis-ci.org/GeekyMoose/elephant-logger-realtime)
[![license](https://img.shields.io/badge/license-Apache-blue.svg)](https://github.com/GeekyMoose/elephant-logger-realtime/blob/dev/LICENSE.txt)

C++ logger library for multi-threads realtime system with printf like format.


> Your code

![screenshot-yourcode](https://i.imgur.com/nqh5U6A.png)

> Execution

![screenshot-result](https://i.imgur.com/CS2Fhiq.png)





# WARNING

## Work in progress
> Work in progress.
> Important changes may happen.
> (Doc may be not UpToDate)

## Performance
> My goal is to implement a logger with high performance.
> However, I haven't done profiling and performance test yet!!
> (My solution could be even slower than simple cout -> profiling required)





# Overview

## Description
This project is a C++ logger designed for Realtime softwares.
In this case, Realtime doesn't mean that logs are displayed in realtime.
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
    - Log max size is 255 char (truncated if higher).
- Outputs
    - Write logs in several outputs.
        - File
        - Cout
        - Visual Studio Console (Cout is not supported)
    - Define your own IOutput implementation.
- Channels
    - Up to 10 channels (ID from 0 to 9)
    - Each channel may be binded to several outputs.
        - Use default configuration for fast use.
        - Set manually outputs in the channels.
- Log configurations
    - Log Level: Bypass all logs with lower critique level.
    - Save: save all logs in safe files.
    - Reset log files at start (Except saved logs).





# Use the library in your project
## Basics
- Build the logger library (Or download the build if available).
- Add elephant `include` path in your project includes path.
- Add static library in your project dependencies.
- Add `#include <elephantlogger/log.h>` into your cpp/h files.
- Call `elephant::initDefault()` in your main.
- You're done!

## Setup channels and outputs
You may either use the default settings or use your custom settings.

### Default Outputs
Simply use `elephantlogger::initDefault()` at the beginning of your program.
This is usually done in the main function.
```
#include <elephantlogger/log.h>
int main(int argc, char** argc) {
    elephantlogger::init();
    // Your code
    return 0;
}
```

Default settings is the following:
- Channel 0
    - Logs in Cout console.
    - Logs in File in TMP folder, with name "elephant-cout.log".
- Channel 1
    - Logs in VS console.
    - Logs in File in TMP folder, with name "elephant-vs.log".
- Channel 2
    - Logs in just one file, in TMP folder, with name "elephant.log"

### Custom Outputs
You may want to manually set outputs to a specific channel (Up to 10).
The steps to follow:
- Include the Output header.
- Create static Output variable.
- Initialize the logger with `init()` (Instead of initDefault).
- Add each output in the channel you want.

WARNING:
It is actually important to respect this order!
(Otherwise, static variable would be destroyed while logger still use them).

> Example

```
// Include Output headers
#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/outputs/LogFile.h"

#include <elephantlogger/log.h>

int main(int argc, char** argc) {
    static elephantlogger::ConsoleCout  coutConsole;
    static elephantlogger::ConsoleVS    visualConsole;
    static elephantlogger::LogFile      logFile("/path/to/log/folder/"   "filename.log");
    static elephantlogger::LogFile      logFileVS("/path/to/log/folder/" "filename.log");

    elephantlogger::init();

    elephantlogger::addOutput(0, &coutConsole);   // Channel 0 logs on cout
    elephantlogger::addOutput(1, &visualConsole); // Channel 1 logs on VS
    elephantlogger::addOutput(2, &logFile);       // Channel 2 logs in file
    elephantlogger::addOutput(1, &logFileVS);     // Channel 1 also log in file

    // Your code
    return 0;
}
```




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


## Build on GNU/Linux from command line
`g++ -I/path/to/elephant/include/ yourProject.cpp /paht/to/libelephantlogger.a -pthread -lstc++fs`
> You may add -g -Wall for debug.


## Execute examples on GNU/Linux with CMake
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
#include "elephantlogger/log.h"

#include <chrono>
#include <thread>


// A simple test
int main(int argc, char** argv) {

    elephantlogger::initDefault(); // Init and set default outputs.

    LOG_WTF(0, "Log wtf (For things that should never happen!)");
    LOG_ERROR(0, "Log an error");
    LOG_WARNING(0, "Warning");
    LOG_CONFIG(0, "Some configuration");
    LOG_INFO(0, "Some information");
    LOG_TRACE(0, "Trace information");
    LOG_DEBUG(0, "The famouse debug!");

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





# Bugs
See the github [issues-section](https://github.com/GeekyMoose/elephant-logger/issues)

> Beware with the format in logs.
> In case of wrong format (Ex: %s instead of %d),
> you may have weird errors without nice warning information.





# Author
- Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
- Logo made by Marie-Pier Bouffard ([www.artstation.com/mariepierbouffard](https://www.artstation.com/mariepierbouffard))
