# Elephant logger

![elephantlogger-logo](logo.png)

[![release-version](https://img.shields.io/badge/release-beta--version-red.svg)](/)
[![Build Status](https://travis-ci.org/GeekyMoose/elephant-logger.svg?branch=dev)](https://travis-ci.org/GeekyMoose/elephant-logger)
[![license](https://img.shields.io/badge/license-Apache-blue.svg)](https://github.com/GeekyMoose/elephant-logger-realtime/blob/dev/LICENSE.txt)

> **WARNING:** This project is now archived.
> I made this project as part of my first steps in C++.
> This was mostly for learning purposes and not targeted for actual production use.
> I'd recommend using mature logging projects instead (such as spdlog).

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

An easy-to-use and flexible C++ logger with support for custom outputs and filters.
The goal is to easily filter and display logs across multiple outputs.

## Features

- Outputs
  - Builtin outputs
    - `LogOutput_File`
    - `LogOutput_Console`
  - Custom outputs
    - Implement the `LogOutput` interface
    - Add `LogOutput` to the logger
- Categories
  - Default category for ease of use
  - Up to 64 categories
  - User-defined categories
- Filters
  - Category filters (global and output-specific)
  - Log level filters (global and output-specific)
  - Filters can be changed at runtime
- Enable/Disable
  - Enable or disable logger
  - Enable or disable a specific output
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
  - `ELEPHANTLOGGER_DISABLED` — Completely disables the logger if defined
  - `ELEPHANTLOGGER_MACROS_DISABLED` — Removes macro definitions (use `elephantlogger::log()` instead)
  - `ELEPHANTLOGGER_ASSERT_ENABLED` — Enables internal assertions for debugging
- Printf-like log format

## Examples

Several examples are available in the `examples/` directory.
Here is a simple example with file output:

```c++
#include <string>
#include <elephantlogger/log.h>
#include <elephantlogger/outputs/LogOutput_File.h>

// Initialize the logger with custom outputs and categories.
static void elephant_customInit() {
    static elephantlogger::LogOutput_File filelog("elephant.log");

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

## Getting Started

- Add the `include/` folder to your project's include paths.
- Add `#include <elephantlogger/log.h>` to your code.
- Call `elephantlogger::init()` in your main function.
- Log using the `LOG_DBG("msg")` macro (replace DBG with any other log level).
- Logs are sent to the default output.

```c++
#include <elephantlogger/log.h>

int main(int argc, char** argc) {
    elephantlogger::init();

    // Your code

    return 0;
}
```

## Build the Examples

- Requirements
  - C++11
  - Pragma support (`#pragma once`)
  - [CMake](https://cmake.org/)

```bash
mkdir build
cd build
cmake -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release ..
make -j2
make run_ex_simple_usage
```

> `DCMAKE_BUILD_TYPE` options: Debug / Release / RelWithDebInfo / MinSizeRel

## Auto-formatting

Auto-formatting uses `clang-format` to apply formatting rules.
You can auto-format all code with the following command:

`clang-format -i -style=file include/**/*.h`

## Generate the Documentation

- In the root folder, run `doxygen Doxyfile`
- Documentation is generated in the `build/doxygen/` folder.

## Known Bugs

- **Warning:** In case of incorrect log format (e.g., using `%s` instead of `%d`), you may encounter obscure errors without helpful warning messages (segmentation fault in the worst case).
- Maximum log size is 255 characters (truncated if longer).
- Windows support has not been tested.

## Authors

- Constantin Masson ([Geekymoose](https://github.com/geekymoose))
- Logo by [Marie-Pier Bouffard](https://www.artstation.com/mariepierbouffard)
