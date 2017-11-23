#pragma once

#include "Logger.h"
#include <stdarg.h>

// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.


namespace elephant {

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

#define LOG_WTF(channelID, format, ...)      elephant::Logger::get().queueLog(elephant::LogLevel::Wtf,      channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(channelID, format, ...)    elephant::Logger::get().queueLog(elephant::LogLevel::Error,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_WARNING(channelID, format, ...)  elephant::Logger::get().queueLog(elephant::LogLevel::Warning,  channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_CONFIG(channelID, format, ...)   elephant::Logger::get().queueLog(elephant::LogLevel::Config,   channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_INFO(channelID, format, ...)     elephant::Logger::get().queueLog(elephant::LogLevel::Info,     channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_TRACE(channelID, format, ...)    elephant::Logger::get().queueLog(elephant::LogLevel::Trace,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_DEBUG(channelID, format, ...)    elephant::Logger::get().queueLog(elephant::LogLevel::Debug,    channelID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
