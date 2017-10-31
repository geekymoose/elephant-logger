#pragma once

// ENTRY POINT for this logger.
// This is the only header to include in your project.

#include "LoggerManager.h"


// -----------------------------------------------------------------------------
// End user macros
// -----------------------------------------------------------------------------

#define LOG_VS_ERROR(msg)       ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Error,     ElephantLogger::LogChannel::Vs,     msg, __FILE__, __LINE__)
#define LOG_VS_WARNING(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Warning,   ElephantLogger::LogChannel::Vs,     msg, __FILE__, __LINE__)
#define LOG_VS_CONFIG(msg)      ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Config,    ElephantLogger::LogChannel::Vs,     msg, __FILE__, __LINE__)
#define LOG_VS_INFO(msg)        ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Info,      ElephantLogger::LogChannel::Vs,     msg, __FILE__, __LINE__)
#define LOG_VS_TRACE(msg)       ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Trace,     ElephantLogger::LogChannel::Vs,     msg, __FILE__, __LINE__)
#define LOG_VS_DEBUG(msg)       ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Debug,     ElephantLogger::LogChannel::Vs,     msg, __FILE__, __LINE__)

#define LOG_COUT_ERROR(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Error,     ElephantLogger::LogChannel::Cout,   msg, __FILE__, __LINE__)
#define LOG_COUT_WARNING(msg)   ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Warning,   ElephantLogger::LogChannel::Cout,   msg, __FILE__, __LINE__)
#define LOG_COUT_CONFIG(msg)    ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Config,    ElephantLogger::LogChannel::Cout,   msg, __FILE__, __LINE__)
#define LOG_COUT_INFO(msg)      ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Info,      ElephantLogger::LogChannel::Cout,   msg, __FILE__, __LINE__)
#define LOG_COUT_TRACE(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Trace,     ElephantLogger::LogChannel::Cout,   msg, __FILE__, __LINE__)
#define LOG_COUT_DEBUG(msg)     ElephantLogger::LoggerManager::getInstance().queueLog(ElephantLogger::LogLevel::Debug,     ElephantLogger::LogChannel::Cout,   msg, __FILE__, __LINE__)

#define LOG_ERROR(msg)          LOG_VS_ERROR(msg)
#define LOG_WARNING(msg)        LOG_VS_WARNING(msg)
#define LOG_CONFIG(msg)         LOG_VS_CONFIG(msg)
#define LOG_INFO(msg)           LOG_VS_INFO(msg)
#define LOG_TRACE(msg)          LOG_VS_TRACE(msg)
#define LOG_DEBUG(msg)          LOG_VS_DEBUG(msg)
