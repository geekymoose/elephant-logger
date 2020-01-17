# Elephant logger

![Elephant-Logger](https://i.imgur.com/vRG1Dsx.png)

[![release-version](https://img.shields.io/badge/release-beta--version-red.svg)](</>)
[![Build Status](https://travis-ci.org/GeekyMoose/elephant-logger.svg?branch=dev)](<https://travis-ci.org/GeekyMoose/elephant-logger>)
[![license](https://img.shields.io/badge/license-Apache-blue.svg)](<https://github.com/GeekyMoose/elephant-logger-realtime/blob/dev/LICENSE.txt>)

C++ logger library for multi-threads realtime system with printf like format.

> Your code

![screenshot-yourcode](https://i.imgur.com/nqh5U6A.png)

> Execution

![screenshot-result](https://i.imgur.com/CS2Fhiq.png)

## Work in progress

I'm doing this for the learning purpose. It is still work in progress, I haven't done any profiling and performance tests so far. (For now, my solution may be even slower than simple cout).

## Description

This project is a C++ logger designed for realtime softwares.
In this case, realtime doesn't actual mean that logs are displayed in realtime.
Instead, my goal is that logging shouldn't affect the programme execution time
(the least we can).
Inside the software thread (your running programme), log calls only queue the message.
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
  - Warning: log max size is 255 char (Truncated if higher).
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

## Getting Started

### Integrate in your project

- Build the logger library (or download a build).
- Add the elephant `include` folder in your project includes path.
- Add the elephantlogger static library in your project build.
- Add `#include <elephantlogger/log.h>` in your cpp/h files.
- Call `elephant::initDefault()` in your main.
- Log things with `LOG_X` macro (change X with the log level).

### Log macros

- `LOG_WTF(channelID, msg)` Log something that should never happen (for strange behavior etc)
- `LOG_ERROR(channelID, msg)` Log an error.
- `LOG_WARNING(channelID, msg)` Log a warning.
- `LOG_CONFIG(channelID, msg)` Log a configuration.
- `LOG_INFO(channelID, msg)` Log an information.
- `LOG_TRACE(channelID, msg)` Log a trace information.
- `LOG_DEBUG(channelID, msg)` Log a debug.

### Use the default Outputs

Use `elephantlogger::initDefault()` at the beginning of your program.
This is usually done in the main function.

```c++
#include <elephantlogger/log.h>

int main(int argc, char** argc) {
    elephantlogger::init();

    // Your code

    return 0;
}
```

Default settings are the following:

- Channel 0
  - Logs in Cout console.
  - Logs in File in TMP folder, with name "elephant-cout.log".
- Channel 1
  - Logs in VS console.
  - Logs in File in TMP folder, with name "elephant-vs.log".
- Channel 2
  - Logs in just one file, in TMP folder, with name "elephant.log"

### Use custom Outputs

You can manually set outputs to a specific channel (up to 10).
The steps to follow:

1. Include the Output header.
1. Create static Output variable.
1. Initialize the logger with `init()` (Instead of initDefault).
1. Add each output in the channel you want.

WARNING:
It is actually important to respect this order
(otherwise, static variable would be destroyed while logger still use them).

### Custom Outputs example

```c++
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

## Build the library

### Requirements

- C++11
- thread (pthread)
- pragma support (pragma once)

### Build on GNU/Linux with CMake

- [CMake](https://cmake.org/)

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j2
```

> DCMAKE_BUILD_TYPE options: Debug / Release / RelWithDebInfo / MinSizeRel

### Build on GNU/Linux from command line

`g++ -I/path/to/elephant/include/ yourProject.cpp /paht/to/libelephantlogger.a -pthread -lstc++fs`

> You may add -g -Wall for debug.

### Execute examples on GNU/Linux with CMake

Set CMake option "BUILD_EXAMPLES" to ON (OFF by default)

```bash
mkdir build
cd build
cmake -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release ..
make -j2
make runExample1 # change 1 by any other example number (e.g., ex2, ex3)
```

> DCMAKE_BUILD_TYPE options: Debug / Release / RelWithDebInfo / MinSizeRel

### Build on Windows

> TODO: Not supported yet.

## Example

> Several examples are available in `examples` directory.

```c++
#include "elephantlogger/log.h"

#include <chrono>
#include <thread>


// A simple test
int main(int argc, char** argv) {

    elephantlogger::initDefault(); // Init and set default outputs.

    LOG_WTF(0, "Log wtf (things that should never happen!)");
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

## Generate documentation

- In the root folder, run `doxygen Doxyfile`
- Documentation generated in build-doxygen folder.

## Known BUGs

See the github [issues-section](https://github.com/GeekyMoose/elephant-logger/issues)

> Warning: in case of wrong log format (e.g., %s instead of %d),
> you will get weird errors without nice warning information (segfault in the worst case).

## Authors

- Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
- Logo made by Marie-Pier Bouffard ([www.artstation.com/mariepierbouffard](https://www.artstation.com/mariepierbouffard))
