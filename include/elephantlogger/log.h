#pragma once

// ENTRY POINT
// This is the only header to include in your project.
// Nellie the elephant will remember everything then


#ifndef ELEPHANTLOGGER_DISABLED

#include <stdarg.h>

#include "elephantlogger/details/config.h"
#include "elephantlogger/details/Logger.h"
#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/outputs/IOutput.h"
#include "elephantlogger/outputs/ConsoleOutput.h"


namespace elephantlogger {

typedef uint64_t LogChannel;

static LogChannel defaultChannel = 1;
static LogChannel noChannels = 0;
static LogChannel allChannels = UINT64_MAX;

/**
 * Initialize the logger and all its subsystems.
 * This creates a ConsoleOutput linked with the default channel.
 * 
 * \param level Maximum level of log to use (uses default if empty).
 */
inline void init(LogLevel level = ELEPHANTLOGGER_DEFAULT_LOGLEVEL) {
    static ConsoleOutput console;
    Logger::get().setLogLevel(level);
    Logger::get().addOutput(&console, level, defaultChannel);
}

/**
 * Adds an output with the given channels filter (reset old filter if exists).
 * Keep a pointer to this output (beware with variable scope).
 *
 * \warning
 * Logger keeps a pointer only, therefore the output variable must live
 * until the logger is stopped (dangling pointer otherwise).
 *
 * \param output    The output to add.
 * \param level     Log level for this output.
 * \param channels  Channels filter for this output.
 */
inline void addOutput(IOutput * output, LogLevel level, LogChannel channels) {
    Logger::get().addOutput(output, level, channels);
}

/**
 * Changes the general log level.
 * This may be called at runtime.
 *
 * \param level Level of log to apply.
 */
inline void setLogLevel(LogLevel level) {
    Logger::get().setLogLevel(level);
}

/**
 * New logs are accepted by the logger.
 */
inline void enableLogger() {
    Logger::get().setEnabled(true);
}

/**
 * New logs are simply bypassed by the logger.
 */
inline void disableLogger() {
    Logger::get().setEnabled(false);
}

/**
 * Set which channels are accepted by the global logger.
 * Any log for a channel that is not in the filter won't be logged.
 */
inline void setChannelsFilter(LogChannel channels) {
    Logger::get().setChannelsFilter(channels);
}

/**
 * All channels are accepted by the logger.
 */
inline void enableAllChannels() {
    Logger::get().enableAllChannels();
}

/**
 * Enable some channels in addition to the channels already enabled.
 */
inline void enableChannels(LogChannel channels) {
    Logger::get().enableChannels(channels);
}

/**
 * Disable the requested channels.
 */
inline void disableChannels(LogChannel channels) {
    Logger::get().disableChannels(channels);
}

/**
 * Logs a message.
 * Accept the message only if LogLevel inferior or equals to current logger level.
 *
 * \param level     Log Level for this message.
 * \param channels  Filter with the channels where to write this log.
 * \param file      File that created the log.
 * \param line      Line position in file.
 * \param function  Function's name.
 * \param format    Row message, using printf convention (%s, %d etc).
 * \param argList   Variable list of parameters.
 */
inline void log(LogLevel level, LogChannel channels, const char * file, int line, const char * function, const char * format, ...) {
    if(Logger::get().passFilters(level, channels)) {
        va_list argList;
        va_start(argList, format);
        Logger::get().log(level, channels, file, line, function, format, argList);
        va_end(argList);
    }
}


#ifndef ELEPHANTLOGGER_MACROS_DISABLED
// Macro may be disabled to avoid collision with existing logger

#define _LOG(level, channelID, format, ...) elephantlogger::log(level, channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

#define LOG_WTF(format, ...)     _LOG(elephantlogger::LogLevel::Debug, 1, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)   _LOG(elephantlogger::LogLevel::Error, 1, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) _LOG(elephantlogger::LogLevel::Warning, 1, format, ##__VA_ARGS__)
#define LOG_CONFIG(format, ...)  _LOG(elephantlogger::LogLevel::Config, 1, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)    _LOG(elephantlogger::LogLevel::Info, 1, format, ##__VA_ARGS__)
#define LOG_TRACE(format, ...)   _LOG(elephantlogger::LogLevel::Trace, 1, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...)   _LOG(elephantlogger::LogLevel::Debug, 1, format, ##__VA_ARGS__)

#define LOG_WTF_IN(channelID, format, ...)     _LOG(elephantlogger::LogLevel::Wtf, channelID, format, ##__VA_ARGS__)
#define LOG_ERROR_IN(channelID, format, ...)   _LOG(elephantlogger::LogLevel::Error, channelID, format, ##__VA_ARGS__)
#define LOG_WARNING_IN(channelID, format, ...) _LOG(elephantlogger::LogLevel::Warning, channelID, format, ##__VA_ARGS__)
#define LOG_CONFIG_IN(channelID, format, ...)  _LOG(elephantlogger::LogLevel::Config, channelID, format, ##__VA_ARGS__)
#define LOG_INFO_IN(channelID, format, ...)    _LOG(elephantlogger::LogLevel::Info, channelID, format, ##__VA_ARGS__)
#define LOG_TRACE_IN(channelID, format, ...)   _LOG(elephantlogger::LogLevel::Trace, channelID, format, ##__VA_ARGS__)
#define LOG_DEBUG_IN(channelID, format, ...)   _LOG(elephantlogger::LogLevel::Debug, channelID, format, ##__VA_ARGS__)

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

typedef uint64_t LogChannel;

static LogChannel defaultChannel = 1;
static LogChannel noChannels = 0;
static LogChannel allChannels = UINT64_MAX;

inline void init(const LogLevel level = ELEPHANTLOGGER_DEFAULT_LOGLEVEL) {}
inline void addOutput(IOutput * output, const LogLevel level, LogChannel channels) {}
inline void setLogLevel(const LogLevel level) {}
inline void enableLogger() {}
inline void disableLogger() {}
inline void setChannelsFilter(LogChannel channels) {}
inline void enableAllChannels() {}
inline void enableChannels(LogChannel channels) {}
inline void disableChannels(LogChannel channels) {}
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

#define LOG_WTF_IN(channelID, format, ...)
#define LOG_ERROR_IN(channelID, format, ...)
#define LOG_WARNING_IN(channelID, format, ...)
#define LOG_CONFIG_IN(channelID, format, ...)
#define LOG_INFO_IN(channelID, format, ...)
#define LOG_TRACE_IN(channelID, format, ...)
#define LOG_DEBUG_IN(channelID, format, ...)

#endif // ELEPHANTLOGGER_MACROS_DISABLED

} // Namespace


#endif // ELEPHANTLOGGER_DISABLED

