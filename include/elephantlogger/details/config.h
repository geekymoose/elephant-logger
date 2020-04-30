#pragma once

#include "elephantlogger/details/LogLevel.h"

// Mostly for internal logger configurations
// WARNING: if you want to change a value, you need to recompile the logger.

namespace elephantlogger {
namespace config {

enum : int
{
    /**
     * Maximum size of the log message's content. (Your message).
     */
    LOG_MSG_SIZE = 256,

    /**
     * Maximum function's name size to display.
     * The function is where the log was generated.
     */
    LOG_FUNCTION_SIZE = 50,

    /**
     * Maximum file size to display.
     * The file is where the log was generated.
     */
    LOG_FILE_SIZE = 200,
};

#define ELEPHANTLOGGER_DEFAULT_LOGLEVEL elephantlogger::LogLevel::Debug

} // End namespace
} // End namespace
