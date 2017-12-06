#pragma once

#include "elephantlogger/logger/Logger.h"
#include "elephantlogger/utils/LoggerAutoInstaller.h"

#include <stdarg.h> // va_args

// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.


namespace elephantlogger {

    /**
     * Initialize the logger and all its subsystem.
     *
     * \warning
     * Must be called once at the beginning. (In main)
     */
    inline void init() {
        // Use of autoinstaller to properly cleanup logger thread before destroyed.
        static LoggerAutoInstaller elephantLoggerEngine;
    }

    /**
     * Save all current logs.
     * Place where logs are saved is defined in configuration.
     *
     * \note
     * Only certain log output are saved (Generally FileLog output).
     * Depends of the actual IOutput implementation.
     */
    inline void saveLogs() {
        Logger::get().saveAllLogFiles();
    }
}


// -----------------------------------------------------------------------------
// End user macros
// -----------------------------------------------------------------------------

#define LOG_WTF(channelID, format, ...)      elephantlogger::Logger::get().queueLog(elephantlogger::LogLevel::Wtf,      channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(channelID, format, ...)    elephantlogger::Logger::get().queueLog(elephantlogger::LogLevel::Error,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARNING(channelID, format, ...)  elephantlogger::Logger::get().queueLog(elephantlogger::LogLevel::Warning,  channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_CONFIG(channelID, format, ...)   elephantlogger::Logger::get().queueLog(elephantlogger::LogLevel::Config,   channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(channelID, format, ...)     elephantlogger::Logger::get().queueLog(elephantlogger::LogLevel::Info,     channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_TRACE(channelID, format, ...)    elephantlogger::Logger::get().queueLog(elephantlogger::LogLevel::Trace,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_DEBUG(channelID, format, ...)    elephantlogger::Logger::get().queueLog(elephantlogger::LogLevel::Debug,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
