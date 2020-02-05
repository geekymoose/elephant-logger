#pragma once

// ENTRY POINT
// This is the only header to include in your project.
// Nellie the elephant will remember everything then.


#ifndef ELEPHANTLOGGER_DISABLED

#include <stdarg.h>

#include "elephantlogger/details/config.h"
#include "elephantlogger/details/Logger.h"
#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/outputs/LogOutput.h"
#include "elephantlogger/outputs/ConsoleLogOutput.h"


namespace elephantlogger {

typedef int LogCategory;

const LogCategory LOG_CATEGORY_DEFAULT = 1;

// Internal use
inline bool isCategoryValid(LogCategory category) {
    // Filter uses 64 bitset. Value range is from 1 to 64
    return category >= 1 && category <= 64;
}


/**
 * Initialize the logger and all its subsystems.
 * This creates a ConsoleLogOutput linked with the default category.
 * 
 * \param level Maximum level of log to use (uses default if empty).
 */
inline void init(LogLevel level = ELEPHANTLOGGER_DEFAULT_LOGLEVEL) {
    static ConsoleLogOutput console;
    Logger::get().filter().setLogLevel(level);
    Logger::get().addOutput(&console, level);
}

/**
 * Adds an output with the given categories filter (reset old filter if exists).
 * Keep a pointer to this output (beware with variable scope).
 *
 * \warning
 * Logger keeps a pointer only, therefore the output variable must live
 * until the logger is stopped (dangling pointer otherwise).
 *
 * \param output The output to add.
 * \param level Log level for this output.
 * \param categories Categories filter for this output.
 */
inline void addOutput(LogOutput * output, LogLevel level) {
    Logger::get().addOutput(output, level);
}

/**
 * Changes the general log level (a.k.a., log severity).
 *
 * \param level New level of log to apply.
 */
inline void setLogLevel(LogLevel level) {
    Logger::get().filter().setLogLevel(level);
}

/**
 * Logs are accepted by the logger.
 */
inline void enableLogger() {
    Logger::get().enable();
}

/**
 * Logs are bypassed by the logger.
 */
inline void disableLogger() {
    Logger::get().disable();
}

/**
 * All categories are accepted by the logger.
 */
inline void enableAllCategoriesLogger() {
    Logger::get().filter().enableAllCategories();
}

/**
 * All categories are bypassed by the logger.
 */
inline void disableAllCategoriesLogger() {
    Logger::get().filter().disableAllCategories();
}

/**
 * Enable the given category in addition to the categories already enabled.
 */
inline void enableCategoryLogger(LogCategory category) {
    ELEPHANTLOGGER_ASSERT(isCategoryValid(category));
    if(isCategoryValid(category)) {
        uint64_t filter = 1 << (category - 1); // Category starts at 1 (not 0)
        Logger::get().filter().enableCategories(filter);
    }
}

/**
 * Disable the given category in addition to the categories already disabled.
 */
inline void disableCategoryLogger(LogCategory category) {
    ELEPHANTLOGGER_ASSERT(isCategoryValid(category));
    if(isCategoryValid(category)) {
        uint64_t filter = 1 << (category - 1); // Category starts at 1 (not 0)
        Logger::get().filter().disableCategories(filter);
    }
}

/**
 * Logs a message.
 * Accept the message only if LogLevel inferior or equals to current logger level.
 *
 * \param level Log Level for this message.
 * \param category Category where to write this log.
 * \param file File that created the log.
 * \param line Line position in file.
 * \param function Function's name.
 * \param format Row message, using printf convention (%s, %d etc).
 * \param argList Variable list of parameters.
 */
inline void log(LogLevel level, LogCategory category, const char * file, int line, const char * function, const char * format, ...) {
    ELEPHANTLOGGER_ASSERT(isCategoryValid(category));
    uint64_t categories_filter = 1 << LOG_CATEGORY_DEFAULT; // Default
    if(isCategoryValid(category)) {
        categories_filter = 1 << (category - 1); // Category starts at 1 (not 0)
    }

    if(Logger::get().isEnabled() && Logger::get().filter().passFilters(level, categories_filter)) {
        va_list argList;
        va_start(argList, format);
        Logger::get().log(level, categories_filter, file, line, function, format, argList);
        va_end(argList);
    }
}


#ifndef ELEPHANTLOGGER_MACROS_DISABLED
// Macro may be disabled to avoid collision with existing logger

#define _LOG(level, categoryID, format, ...) elephantlogger::log(level, categoryID, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)

#define LOG_WTF(format, ...)     _LOG(elephantlogger::LogLevel::Debug, elephantlogger::LOG_CATEGORY_DEFAULT, __FILE__, __LINE__, __FUNCTION__, format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...)   _LOG(elephantlogger::LogLevel::Error, elephantlogger::LOG_CATEGORY_DEFAULT, format, ##__VA_ARGS__)
#define LOG_WARNING(format, ...) _LOG(elephantlogger::LogLevel::Warning, elephantlogger::LOG_CATEGORY_DEFAULT, format, ##__VA_ARGS__)
#define LOG_CONFIG(format, ...)  _LOG(elephantlogger::LogLevel::Config, elephantlogger::LOG_CATEGORY_DEFAULT, format, ##__VA_ARGS__)
#define LOG_INFO(format, ...)    _LOG(elephantlogger::LogLevel::Info, elephantlogger::LOG_CATEGORY_DEFAULT, format, ##__VA_ARGS__)
#define LOG_TRACE(format, ...)   _LOG(elephantlogger::LogLevel::Trace, elephantlogger::LOG_CATEGORY_DEFAULT, format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...)   _LOG(elephantlogger::LogLevel::Debug, elephantlogger::LOG_CATEGORY_DEFAULT, format, ##__VA_ARGS__)

#define LOG_WTF_IN(categoryID, format, ...)     _LOG(elephantlogger::LogLevel::Wtf, categoryID, format, ##__VA_ARGS__)
#define LOG_ERROR_IN(categoryID, format, ...)   _LOG(elephantlogger::LogLevel::Error, categoryID, format, ##__VA_ARGS__)
#define LOG_WARNING_IN(categoryID, format, ...) _LOG(elephantlogger::LogLevel::Warning, categoryID, format, ##__VA_ARGS__)
#define LOG_CONFIG_IN(categoryID, format, ...)  _LOG(elephantlogger::LogLevel::Config, categoryID, format, ##__VA_ARGS__)
#define LOG_INFO_IN(categoryID, format, ...)    _LOG(elephantlogger::LogLevel::Info, categoryID, format, ##__VA_ARGS__)
#define LOG_TRACE_IN(categoryID, format, ...)   _LOG(elephantlogger::LogLevel::Trace, categoryID, format, ##__VA_ARGS__)
#define LOG_DEBUG_IN(categoryID, format, ...)   _LOG(elephantlogger::LogLevel::Debug, categoryID, format, ##__VA_ARGS__)

#endif // ELEPHANTLOGGER_MACROS_DISABLED

} // Namespace


// -----------------------------------------------------------------------------

#else // ELEPHANTLOGGER_DISABLED

// Totally disable the elephant logger library
// Any logger call are replaced by an empty method

#include "details/LogLevel.h"
#include "details/config.h"
#include "outputs/LogOutput.h"


namespace elephantlogger {

typedef uint64_t LogCategory;

static LogCategory defaultCategory = 1;
static LogCategory noCategories = 0;
static LogCategory allCategories = UINT64_MAX;

inline void init(const LogLevel level = ELEPHANTLOGGER_DEFAULT_LOGLEVEL) {}
inline void addOutput(LogOutput * output, const LogLevel level, LogCategory categories) {}
inline void setLogLevel(const LogLevel level) {}
inline void enableLogger() {}
inline void disableLogger() {}
inline void setCategoriesFilter(LogCategory categories) {}
inline void enableAllCategories() {}
inline void enableCategories(LogCategory categories) {}
inline void disableCategories(LogCategory categories) {}
inline void log(const LogLevel level, const int categoryID, const char* file,
                const int line, const char* function, const char* format, ...) {}

#ifndef ELEPHANTLOGGER_MACROS_DISABLED

#define LOG_WTF(format, ...)
#define LOG_ERROR(format, ...)
#define LOG_WARNING(format, ...)
#define LOG_CONFIG(format, ...)
#define LOG_INFO(format, ...)
#define LOG_TRACE(format, ...)
#define LOG_DEBUG(format, ...)

#define LOG_WTF_IN(categoryID, format, ...)
#define LOG_ERROR_IN(categoryID, format, ...)
#define LOG_WARNING_IN(categoryID, format, ...)
#define LOG_CONFIG_IN(categoryID, format, ...)
#define LOG_INFO_IN(categoryID, format, ...)
#define LOG_TRACE_IN(categoryID, format, ...)
#define LOG_DEBUG_IN(categoryID, format, ...)

#endif // ELEPHANTLOGGER_MACROS_DISABLED

} // Namespace


#endif // ELEPHANTLOGGER_DISABLED

