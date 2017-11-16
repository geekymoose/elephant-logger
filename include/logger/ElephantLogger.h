#pragma once

// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.

#include "Logger.h"


namespace ElephantLogger {

    /**
     * Initialize the logger and all its subsystem..
     * Must be called once at the beginning.
     */
    void init() {
        ElephantLogger::Logger::get().startup();
    }
}


// -----------------------------------------------------------------------------
// End user macros
// -----------------------------------------------------------------------------

#define LOG_WTF(channelID, msg)      ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Wtf,      channelID, msg, __FILE__, __LINE__)
#define LOG_ERROR(channelID, msg)    ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Error,    channelID, msg, __FILE__, __LINE__)
#define LOG_WARNING(channelID, msg)  ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Warning,  channelID, msg, __FILE__, __LINE__)
#define LOG_CONFIG(channelID, msg)   ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Config,   channelID, msg, __FILE__, __LINE__)
#define LOG_INFO(channelID, msg)     ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Info,     channelID, msg, __FILE__, __LINE__)
#define LOG_TRACE(channelID, msg)    ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Trace,    channelID, msg, __FILE__, __LINE__)
#define LOG_DEBUG(channelID, msg)    ElephantLogger::Logger::get().queueLog(ElephantLogger::LogLevel::Debug,    channelID, msg, __FILE__, __LINE__)
