#pragma once
#include "core/LogLevel.h"
#include <stdarg.h> // va_args


// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.


namespace elephantlogger {

class IOutput;


    /**
     * Initialize the logger and all its subsystem.
     *
     * \warning
     * Must be called once at the beginning. (In main)
     */
    void init();

    /**
     * Save all current logs.
     * Logs are placed in same logFilePath, with special date format prefix.
     *
     * \note
     * Only certain log output are saved (Generally FileLog output).
     * Depends of the actual IOutput implementation.
     */
    void saveLogs();

    /**
     * Add an Output to the specific channel.
     * This channel now write logs in this output as well.
     *
     * \note
     * Channel keeps a pointer only.
     * The output variable must live until you manually remove it from channel
     * or close the whole logger.
     */
    void addOutput(const int channelID, IOutput* output);

    /**
     * Change the log level.
     *
     * \param level LogLevel to apply.
     */
    void setLogLevel(const LogLevel level);

    /**
     * Change the path where log files are places.
     *
     * \warning
     * No validity check.
     *
     * \param path Where to place logs.
     */
    void setLogFilePath(const char* path);

    /**
     * This set the channels with default outputs linked with them.
     *
     * \note
     * This is usually called at the begining for fast configuration.
     */
    void setDefaultChannels();

    /**
     * Log a message. (If log level accept the given value).
     *
     * \param level     Log Level for this message.
     * \param channelID ID of the channel where to write log.
     * \param file      File that created the log
     * \param line      Line position in file.
     * \param function  Function's name.
     * \param format    Row message, using printf convention (%s, %d etc).
     * \param argList   Variable list of parameters.
     */
    void log(const LogLevel level,
             const int channelID,
             const char* file,
             const int line,
             const char* function,
             const char* format,
             ...);
}


// -----------------------------------------------------------------------------
// End user macros
// -----------------------------------------------------------------------------

#define LOG_WTF(channelID, format, ...)     elephantlogger::log(elephantlogger::LogLevel::Wtf,      channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(channelID, format, ...)   elephantlogger::log(elephantlogger::LogLevel::Error,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARNING(channelID, format, ...) elephantlogger::log(elephantlogger::LogLevel::Warning,  channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_CONFIG(channelID, format, ...)  elephantlogger::log(elephantlogger::LogLevel::Config,   channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(channelID, format, ...)    elephantlogger::log(elephantlogger::LogLevel::Info,     channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_TRACE(channelID, format, ...)   elephantlogger::log(elephantlogger::LogLevel::Trace,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_DEBUG(channelID, format, ...)   elephantlogger::log(elephantlogger::LogLevel::Debug,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)


