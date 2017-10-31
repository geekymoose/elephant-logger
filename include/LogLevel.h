#pragma once

#include "cstdint" // For int8_t


namespace ElephantLogger {


/**
 * Defines the level of logs.
 * Lowest value is for more critical logs. (Error < DEBUG).
 * int8_t is only for little place optim to use with atomic_int8_t.
 */
enum class LogLevel : int8_t {
    Error,          // Lowest Log level: Critical.
    Warning,        // Log that is not critical but may represent a threat.
    Config,         // Configuration log.
    Info,           // Informative log about engine execution.
    Trace,          // Informative log that are less important.
    Debug,          // For debug.

    // Internal
    LogLevelSize    // Enum's size: Number of defined LogLevels (TO KEEP LAST).
};


} // End namespace
