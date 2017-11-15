#pragma once

#include "cstdint" // For int8_t


namespace ElephantLogger {


/**
 * Defines the level of logs.
 * Lowest value is for more critical logs. (ex: Error < DEBUG).
 *
 * \remark
 * int8_t is only for little place optim to use with atomic_int8_t.
 * (Though it's probably not that usefull).
 *
 * \author  Constantin Masson
 * \since   1.0
 */
enum LogLevel : std::int8_t {
    Wtf = 0,        // What the fuck: Something that may have never happened.
    Error,          // Lowest Log level: Critical.
    Warning,        // Log that is not critical but may represent a threat.
    Config,         // Configuration log.
    Info,           // Informative log about engine execution.
    Trace,          // Informative log that are less important.
    Debug,          // For debug.


    // Internal
    Size            // Enum's size: Number of defined LogLevels (TO KEEP LAST).
};

class LogLevelHelper {
    private:
        LogLevelHelper() = delete;
        ~LogLevelHelper() = delete;
    public:
        static const char* logLevelToString(LogLevel level) {
            switch(level) {
                case LogLevel::Error:
                    return "Error";
                case LogLevel::Warning:
                    return "Warning";
                case LogLevel::Config:
                    return "Config";
                case LogLevel::Info:
                    return "Info";
                case LogLevel::Trace:
                    return "Trace";
                case LogLevel::Debug:
                    return "Debug";
                default:
                    return "WTF";
            }
        }
};


} // End namespace

