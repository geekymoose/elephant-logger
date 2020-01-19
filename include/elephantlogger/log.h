#pragma once

// ENTRY POINT
// This is the only header to include in your project.
// Nellie the elephant will remember everything then


#ifndef ELEPHANTLOGGER_DISABLED

#include <stdarg.h>

#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/config.h"
#include "elephantlogger/outputs/IOutput.h"
#include "elephantlogger/outputs/ConsoleOutput.h"

#ifdef ELEPHANTLOGGER_MULTITHREADS_ENABLED
#   include "elephantlogger/details/LoggerMultithreads.h"
#else
#   include "elephantlogger/details/Logger.h"
#endif


namespace elephantlogger {

/**
 * Initialize the logger and all its subsystems.
 * By default, the first channel has a ConsoleOutput setup.
 * This method must be called once before any log call..
 * 
 * \param level Maximum level of log to use (uses default if empty).
 */
inline void init(const LogLevel level = ELEPHANTLOGGER_DEFAULT_LOGLEVEL) {
    static ConsoleOutput console;
    Logger::get().addOutput(0, &console);
    Logger::get().setLogLevel(level);
}

/**
 * Adds an Output to the specific channel.
 * Do nothing in case of invalid ID or nullptr.
 *
 * \warning
 * Channel keeps a pointer only, therefore the output variable must live
 * until the logger is stopped (dangling pointer otherwise).
 *
 * \param channelID ID of the channel where to add output.
 * \param output Pointer to the output instance (do nothing if null).
 */
inline void addOutput(const int channelID, IOutput * output) {
    Logger::get().addOutput(channelID, output);
}

/**
 * Changes the log level.
 * This may be called at runtime.
 *
 * \param level New level of log to apply.
 */
inline void setLogLevel(const LogLevel level) {
    Logger::get().setLogLevel(level);
}

/**
 * Logs a message.
 * Accept the message only if LogLevel inferior or equals to current logger level.
 *
 * \param level     Log Level for this message.
 * \param channelID ID of the channel where to write log.
 * \param file      File that created the log
 * \param line      Line position in file.
 * \param function  Function's name.
 * \param format    Row message, using printf convention (%s, %d etc).
 * \param argList   Variable list of parameters.
 */
inline void log(const LogLevel level,
                const int channelID,
                const char * file,
                const int line,
                const char * function,
                const char * format,
                ...) {
    if(Logger::get().isLogLevelAccepted(level)) {
        va_list argList;
        va_start(argList, format);
        Logger::get().log(level, channelID, file, line, function, format, argList);
        va_end(argList);
    }
}


#ifndef ELEPHANTLOGGER_MACROS_DISABLED
// Macro may be disabled to avoid collision with existing logger

#define _LOG(level, channelID, format, ...) elephantlogger::log(level, channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

#define LOG_WTF(format, ...)     _LOG(elephantlogger::LogLevel::Wtf, 0, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)   _LOG(elephantlogger::LogLevel::Error, 0, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) _LOG(elephantlogger::LogLevel::Warning, 0, format, ##__VA_ARGS__)
#define LOG_CONFIG(format, ...)  _LOG(elephantlogger::LogLevel::Config, 0, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)    _LOG(elephantlogger::LogLevel::Info, 0, format, ##__VA_ARGS__)
#define LOG_TRACE(format, ...)   _LOG(elephantlogger::LogLevel::Trace, 0, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...)   _LOG(elephantlogger::LogLevel::Debug, 0, format, ##__VA_ARGS__)

#define LOG_WTF_(channelID, format, ...)     _LOG(elephantlogger::LogLevel::Wtf, channelID, format, ##__VA_ARGS__)
#define LOG_ERROR_(channelID, format, ...)   _LOG(elephantlogger::LogLevel::Error, channelID, format, ##__VA_ARGS__)
#define LOG_WARNING_(channelID, format, ...) _LOG(elephantlogger::LogLevel::Warning, channelID, format, ##__VA_ARGS__)
#define LOG_CONFIG_(channelID, format, ...)  _LOG(elephantlogger::LogLevel::Config, channelID, format, ##__VA_ARGS__)
#define LOG_INFO_(channelID, format, ...)    _LOG(elephantlogger::LogLevel::Info, channelID, format, ##__VA_ARGS__)
#define LOG_TRACE_(channelID, format, ...)   _LOG(elephantlogger::LogLevel::Trace, channelID, format, ##__VA_ARGS__)
#define LOG_DEBUG_(channelID, format, ...)   _LOG(elephantlogger::LogLevel::Debug, channelID, format, ##__VA_ARGS__)

#endif // ELEPHANTLOGGER_MACROS_DISABLED

} // Namespace


// -----------------------------------------------------------------------------

#else // ELEPHANTLOGGER_DISABLED

// Totally disable the elephant logger library
// Any logger call are replaced by an empty method

#include "details/LogLevel.h"
#include "details/config.h"
#include "outputs/IOutput.h"


namespace elephantlogger {

inline void init(const LogLevel level = ELEPHANTLOGGER_DEFAULT_LOGLEVEL) {}
inline void addOutput(const int channelID, IOutput * output) {}
inline void setLogLevel(const LogLevel level) {}
inline void log(const LogLevel level, const int channelID, const char* file,
         const int line, const char* function, const char* format, ...) {}

#ifndef ELEPHANTLOGGER_MACROS_DISABLED

#define LOG_WTF(format, ...)
#define LOG_ERROR(format, ...)
#define LOG_WARNING(format, ...)
#define LOG_CONFIG(format, ...)
#define LOG_INFO(format, ...)
#define LOG_TRACE(format, ...)
#define LOG_DEBUG(format, ...)

#define LOG_WTF_(channelID, format, ...)
#define LOG_ERROR_(channelID, format, ...)
#define LOG_WARNING_(channelID, format, ...)
#define LOG_CONFIG_(channelID, format, ...)
#define LOG_INFO_(channelID, format, ...)
#define LOG_TRACE_(channelID, format, ...)
#define LOG_DEBUG_(channelID, format, ...)

#endif // ELEPHANTLOGGER_MACROS_DISABLED

} // Namespace


#endif // ELEPHANTLOGGER_DISABLED

