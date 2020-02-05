# Elephant logger

![elephantlogger-logo](logo.png)

[![release-version](https://img.shields.io/badge/release-beta--version-red.svg)](</>)
[![Build Status](https://travis-ci.org/GeekyMoose/elephant-logger.svg?branch=dev)](<https://travis-ci.org/GeekyMoose/elephant-logger>)
[![license](https://img.shields.io/badge/license-Apache-blue.svg)](<https://github.com/GeekyMoose/elephant-logger-realtime/blob/dev/LICENSE.txt>)

```c++
// Your code
#include <elephantlogger/log.h>

int main(int argc, char** argv) {

    elephantlogger::init();

    LOG_WTF("Log WTF");
    LOG_ERROR("Log error");
    LOG_WARNING("Log warning");
    LOG_CONFIG("Log config");
    LOG_INFO("Log info");
    LOG_TRACE("Log trace");
    LOG_DEBUG("Log debug");

    LOG_DEBUG("Integer value: %d", 42);
    LOG_DEBUG("Float value: %f", 31.9);
    LOG_DEBUG("Bool value (true): %d", true);
    LOG_DEBUG("NULL (Using d): %d", NULL);
    LOG_DEBUG("NULL (Using s): %s", NULL);

    LOG_DEBUG("String: %s / Integer: %d / Float: %f / Char: %c", "Hello", 2, 7.1, 'c');

    int counter = 0;
    while(counter < 12) {
        counter++;
        LOG_DEBUG("Log in loop (counter: %d)", counter);
    }

    return 0;
}
```

## Description

Easy to use and flexible C++ logger with support for custom outputs and filters.
The goal is to easily filter and show the logs on several outputs.

## Work in progress

- API may change.
- Not thread safe for now.
- Warning: max log size is 255 chars (truncated if higher).
- No Windows support tested.
- Add color console output.

## Features

- Outputs
  - Builtin outputs
    - `FileLogOutput`
    - `ConsoleLogOutput`
  - Custom outputs
    - Implement `LogOutput` interface
    - Add `LogOutput` in the logger
- Categories
  - Default category for easy usage
  - Up to 64 categories
  - User defined categories
- Filters
  - Category filters (global and output specific)
  - Log level filters (global and output specific)
  - Filters can be changed at runtime
- Enable / disable
  - Enable logger
  - Disable logger
  - Enable a specific output
  - Disable a specific output
- Default logging macros
  - `LOG_WTF(msg, ...)`
  - `LOG_ERROR(msg, ...)`
  - `LOG_WARNING(msg, ...)`
  - `LOG_CONFIG(msg, ...)`
  - `LOG_INFO(msg, ...)`
  - `LOG_TRACE(msg, ...)`
  - `LOG_DEBUG(msg, ...)`
- Category logging macros
  - `LOG_WTF_IN(categoryID, msg, ...)`
  - `LOG_ERROR_IN(categoryID, msg, ...)`
  - `LOG_WARNING_IN(categoryID, msg, ...)`
  - `LOG_CONFIG_IN(categoryID, msg, ...)`
  - `LOG_INFO_IN(categoryID, msg, ...)`
  - `LOG_TRACE_IN(categoryID, msg, ...)`
  - `LOG_DEBUG_IN(categoryID, msg, ...)`
- Configuration macros
  - `ELEPHANTLOGGER_DISABLED` Totally disable the logger if defined
  - `ELEPHANTLOGGER_MACROS_DISABLED` Remove the macro definitions (use `elephantlogger::log()` instead)
  - `ELEPHANTLOGGER_ASSERT_ENABLED` Enable internal assert for debug
- Printf like log format

## Getting Started

- Add the `include/` folder in your project's include paths.
- Add `#include <elephantlogger/log.h>` in your code.
- Call `elephantlogger::init()` in your main.
- Log using `LOG_DBG("msg")` macro (change DGB with any other log levels).
- Logs are sent to the default output.

```c++
#include <elephantlogger/log.h>

int main(int argc, char** argc) {
    elephantlogger::init();

    // Your code

    return 0;
}
```

## Example with a file output

```c++
#include <string>
#include <elephantlogger/log.h>
#include <elephantlogger/outputs/FileLogOutput.h>

// Initialize the logger with custom outputs and categories.
static void elephant_customInit() {
    static elephantlogger::FileLogOutput filelog("elephant.log");

    elephantlogger::init();
    elephantlogger::addOutput(&filelog, elephantlogger::LogLevel::Debug);
}

int main(int argc, char** argv) {
    elephant_customInit();

    LOG_WARNING("Some warning log");
    LOG_DEBUG("Some debug log");
    LOG_ERROR("Some error log");
    LOG_CONFIG("Some config log");
    LOG_TRACE("Some trace log");
    LOG_INFO("Some information log");

    return 0;
}
```

## Build the examples

### Requirements

- C++11
- pragma support (pragma once)

### Build the examples on GNU/Linux with CMake

- [CMake](https://cmake.org/)

```bash
mkdir build
cd build
cmake -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release ..
make -j2
make run_ex_simple_usage
```

> DCMAKE_BUILD_TYPE options: Debug / Release / RelWithDebInfo / MinSizeRel

## Examples of codes

Several examples are available in the `examples` directory.

## Generate the documentation

- In the root folder, run `doxygen Doxyfile`
- Documentation generated in build-doxygen folder.

## Known BUGs

See the github [issues-section](https://github.com/GeekyMoose/elephant-logger/issues)

> Warning: in case of wrong log format (e.g., %s instead of %d),
> you will get weird errors without nice warning information (segfault in the worst case).

## Authors

- Constantin Masson ([GeekyMoose](https://github.com/GeekyMoose))
- Logo made by Marie-Pier Bouffard ([www.artstation.com/mariepierbouffard](https://www.artstation.com/mariepierbouffard))
