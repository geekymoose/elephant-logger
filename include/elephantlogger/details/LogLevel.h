#pragma once


namespace elephantlogger {

/**
 * Defines the level of logs (a.k.a., severity).
 * The lowest value is for more critical logs (e.g., Error < Debug).
 */
enum LogLevel : int {
    Wtf = 0,        // Something that should never happen.
    Error,          // Critical error.
    Warning,        // Log that is not critical but may represent a threat.
    Config,         // Configuration log.
    Info,           // Information about the execution.
    Trace,          // Trace some execution.
    Debug,          // For debug.

    // Internal
    COUNT           // Enum's size: Number of LogLevels (KEEP IT LAST).
};

inline const char* logLevelToString(LogLevel level) {
    switch(level) {
        case LogLevel::Wtf:
            return "WTF";
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
            return "Unknown";
    }
}


}

