#pragma once

// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.

#include "Logger.h"

#include <stdarg.h>
#include <stdio.h>


namespace ElephantLogger {

    /**
     * Initialize the logger and all its subsystem.
     * Must be called once at the beginning.
     */
    inline void init() {
        Logger::get().startup();
    }
}


// -----------------------------------------------------------------------------
// End user macros
// -----------------------------------------------------------------------------

#define LOG_WTF(channelID, format, ...)      ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Wtf,      channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(channelID, format, ...)    ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Error,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARNING(channelID, format, ...)  ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Warning,  channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_CONFIG(channelID, format, ...)   ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Config,   channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(channelID, format, ...)     ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Info,     channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_TRACE(channelID, format, ...)    ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Trace,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_DEBUG(channelID, format, ...)    ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Debug,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
