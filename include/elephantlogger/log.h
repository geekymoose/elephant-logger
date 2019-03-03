#pragma once

#include <stdarg.h>

#include "core/LogLevel.h"


// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.


namespace elephantlogger {

class IOutput;


/**
 * Initialize the logger and all its subsystems.
 * By default, the first channel has a ConsoleOutput setup.
 * This method must be called once before any loggin call.
 */
void init();

/**
 * Adds an Output to the specific channel.
 *
 * \warning
 * Channel keeps a pointer only, therefore the output variable must live
 * until the logger is stopped (dangling pointer otherwise).
 *
 * \param channelID Channel where to add output.
 * \param output Pointer to the output. Do nothing if null.
 */
void addOutput(const int channelID, IOutput * output);

/**
 * Change the log level.
 *
 * \param level LogLevel to apply.
 */
void setLogLevel(const LogLevel level);

/**
 * Log a message.
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
void log(const LogLevel level,
         const int channelID,
         const char* file,
         const int line,
         const char* function,
         const char* format,
         ...);


} // End namespace


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

