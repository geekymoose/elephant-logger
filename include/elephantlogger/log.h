#pragma once
#include "core/LogLevel.h"
#include <stdarg.h>


// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.


namespace elephantlogger {
class IOutput;


/**
 * Initialize the logger and all its subsystems.
 *
 * \warning
 * Must be called once at the beginning. (Ex: in main)
 */
void init();

/**
 * Initialize the logger and all its subsystems.
 * Set channels with default outputs.
 *
 * \warning
 * Must be called once at the beginning. (Ex: In main)
 */
void initDefault();

/**
 * Save all current logs.
 * Logs are placed in same current path set for logger and add date prefix.
 *
 * \note
 * Only certain log output are saved (Generally FileLog output).
 * Depends of the actual IOutput implementation.
 */
void saveLogs(const char* path);

/**
 * Add an Output to the specific channel.
 * This channel now write logs in this output as well.
 *
 * \note
 * Channel keeps a pointer only.
 * The output variable must live until you manually remove it from channel
 * or close the whole logger.
 *
 * \warning
 * Undefined behavior if output freed while logger still use it.
 */
void addOutput(const int channelID, IOutput* output);

/**
 * Change the log level.
 *
 * \param level LogLevel to apply.
 */
void setLogLevel(const LogLevel level);

/**
 * Returns the temporary file path.
 * Ex: /tmp/ on Linux or %TEMP% on Windows.
 *
 * \return Path to temporary folder.
 */
const char* getTmpFilePath();

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


