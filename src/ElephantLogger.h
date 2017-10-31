#pragma once

// THIS IS THE ENTRY POINT FOR THE END USER.
// The only header to include in his project.

#include "LoggerManager.h"


// -----------------------------------------------------------------------------
// End user macros
// -----------------------------------------------------------------------------

#define LOG_VS_ERROR(msg)       MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Error,  MoonRPG::LogChannel::Vs, msg, __FILE__, __LINE__)
#define LOG_VS_WARNING(msg)     MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Warning,MoonRPG::LogChannel::Vs, msg, __FILE__, __LINE__)
#define LOG_VS_CONFIG(msg)      MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Config, MoonRPG::LogChannel::Vs, msg, __FILE__, __LINE__)
#define LOG_VS_INFO(msg)        MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Info,   MoonRPG::LogChannel::Vs, msg, __FILE__, __LINE__)
#define LOG_VS_TRACE(msg)       MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Trace,  MoonRPG::LogChannel::Vs, msg, __FILE__, __LINE__)
#define LOG_VS_DEBUG(msg)       MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Debug,  MoonRPG::LogChannel::Vs, msg, __FILE__, __LINE__)

#define LOG_COUT_ERROR(msg)     MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Error,  MoonRPG::LogChannel::Cout, msg, __FILE__, __LINE__)
#define LOG_COUT_WARNING(msg)   MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Warning,MoonRPG::LogChannel::Cout, msg, __FILE__, __LINE__)
#define LOG_COUT_CONFIG(msg)    MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Config, MoonRPG::LogChannel::Cout, msg, __FILE__, __LINE__)
#define LOG_COUT_INFO(msg)      MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Info,   MoonRPG::LogChannel::Cout, msg, __FILE__, __LINE__)
#define LOG_COUT_TRACE(msg)     MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Trace,  MoonRPG::LogChannel::Cout, msg, __FILE__, __LINE__)
#define LOG_COUT_DEBUG(msg)     MoonRPG::LoggerManager::instance().queueLog(MoonRPG::LogLevel::Debug,  MoonRPG::LogChannel::Cout, msg, __FILE__, __LINE__)

#define LOG_ERROR(msg)          LOG_VS_ERROR(msg)
#define LOG_WARNING(msg)        LOG_VS_WARNING(msg)
#define LOG_CONFIG(msg)         LOG_VS_CONFIG(msg)
#define LOG_INFO(msg)           LOG_VS_INFO(msg)
#define LOG_TRACE(msg)          LOG_VS_TRACE(msg)
#define LOG_DEBUG(msg)          LOG_VS_DEBUG(msg)