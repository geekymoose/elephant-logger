# Elephant Logger

> Your code

![Screenshot - Code](https://i.imgur.com/KNjvr4G.png)

> Execution

![Screenshot - Example1](https://i.imgur.com/cIqhS2s.png)


# Work in progress
Only at a kind of alpha state for now.

> Coming soon

- Compile as a static library
- Cleanup options management


# Description
This project is a C++ logger designed for Realtime softwares.
The goal is that logging shouldn't affect the programme execution time. (The least we can).
Inside the software thread (Your running programme), log calls only queue the message.
The logger is started on its own thread which then process the logs, print them, write in files etc...


# Dependencies
- No dependency


# Build requirement
- C++11
- experimental/filesystem support
- pragma support (pragma once)


# Build / Run on Linux (CMake)
- [CMake](https://cmake.org/)
- Use flags c++11 and lstdc++fs (for experimental/filesystem)

```
mkdir build
cd build
cmake ..
make -j4
make run
```


# Build / Run on Windows
TODO (Windows supported)


# Features
- Simple logging calls (Use default output channel)
    - LOG_ERROR
    - LOG_WARNING
    - LOG_CONFIG
    - LOG_INFO
    - LOG_TRACE
    - LOG_DEBUG
- Log in specific channel
    - LOG_COUT_X (Log in std::cout. Replace X by LogLevel)
    - LOG_VS_X (Log in Visual studio console, or std::cout in linux. Replace X by LogLevel)
- Logging options
    - Log Level (Bypass all logs with lower critique level)
    - Log in file: ON / OFF
    - Save log file
    - Reset log file at start
    - Multi channel logs (Output in Cout, on Visual Studio)
- Cross Platform
    - Linux
    - Windows


# Example
```
#include "ElephantLogger.h"
#include <chrono>
#include <thread>

int main(int argc, char** argv) {

    ElephantLogger::LoggerManager::getInstance().initialize();

    LOG_ERROR("1. TEST ERROR");
    LOG_WARNING("2. TEST WARNING");
    LOG_CONFIG("3. TEST CONFIG");
    LOG_INFO("4. TEST INFO");
    LOG_TRACE("5. TEST TRACE");
    LOG_DEBUG("6. TEST DEBUG");

    while(true) {
        LOG_DEBUG("Debug in loop");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
```


# Generate Doxygen documentation
- `doxygen Doxyfile`
- Documentation generated in build-doxygen folder.


# Author
Constantin Masson ([constantinmasson.com](http://constantinmasson.com/))
