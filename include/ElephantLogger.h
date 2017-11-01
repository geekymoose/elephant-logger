#pragma once

// ENTRY POINT for this terrible Elephant Logger.
// This is the only header to include in your project.

#include "LoggerManager.h"


// -----------------------------------------------------------------------------
// End user macros
// -----------------------------------------------------------------------------

#define LOG_ERROR_VS(msg)       ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Error,  ElephantLogger::LogOutputType::Vs,     msg, __FILE__, __LINE__)
#define LOG_WARNING_VS(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Warning,ElephantLogger::LogOutputType::Vs,     msg, __FILE__, __LINE__)
#define LOG_CONFIG_VS(msg)      ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Config, ElephantLogger::LogOutputType::Vs,     msg, __FILE__, __LINE__)
#define LOG_INFO_VS(msg)        ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Info,   ElephantLogger::LogOutputType::Vs,     msg, __FILE__, __LINE__)
#define LOG_TRACE_VS(msg)       ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Trace,  ElephantLogger::LogOutputType::Vs,     msg, __FILE__, __LINE__)
#define LOG_DEBUG_VS(msg)       ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Debug,  ElephantLogger::LogOutputType::Vs,     msg, __FILE__, __LINE__)

#define LOG_ERROR_COUT(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Error,  ElephantLogger::LogOutputType::Cout,   msg, __FILE__, __LINE__)
#define LOG_WARNING_COUT(msg)   ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Warning,ElephantLogger::LogOutputType::Cout,   msg, __FILE__, __LINE__)
#define LOG_CONFIG_COUT(msg)    ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Config, ElephantLogger::LogOutputType::Cout,   msg, __FILE__, __LINE__)
#define LOG_INFO_COUT(msg)      ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Info,   ElephantLogger::LogOutputType::Cout,   msg, __FILE__, __LINE__)
#define LOG_TRACE_COUT(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Trace,  ElephantLogger::LogOutputType::Cout,   msg, __FILE__, __LINE__)
#define LOG_DEBUG_COUT(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Debug,  ElephantLogger::LogOutputType::Cout,   msg, __FILE__, __LINE__)

#define LOG_ERROR(msg)          LOG_ERROR_VS(msg)
#define LOG_WARNING(msg)        LOG_WARNING_VS(msg)
#define LOG_CONFIG(msg)         LOG_CONFIG_VS(msg)
#define LOG_INFO(msg)           LOG_INFO_VS(msg)
#define LOG_TRACE(msg)          LOG_TRACE_VS(msg)
#define LOG_DEBUG(msg)          LOG_DEBUG_VS(msg)
