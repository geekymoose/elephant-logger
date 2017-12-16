#pragma once


namespace elephantlogger {


/**
 * Defines the level of logs.
 * Lowest value is for more critical logs. (ex: Error < DEBUG).
 *
 * \author  Constantin Masson
 * \since   1.0
 */
enum LogLevel : int {
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


/**
 * Abstract class with only static methods.
 * Helper for LogLevel enum.
 *
 * \author  Constantin Masson
 * \since   1.0
 */
class LogLevelHelper {
    private:
        LogLevelHelper() = delete;
        ~LogLevelHelper() = delete;

    public:
        static const char* logLevelToString(LogLevel level) {
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
};


} // End namespace

