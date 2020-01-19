#pragma once

#include "LogLevel.h"


// Mostly for internal logger configurations
// WARNING: if you want to change a value, you need to recompile the logger.


namespace elephantlogger {
namespace config {

enum : int {

    /**
     * Max size of the message content of a log. (Your message).
     */
    LOG_MSG_SIZE = 256,

    /**
     * Max size of the function name in log message.
     */
    LOG_FUNCTION_SIZE = 50,

    /**
     * Max size of the displayed file name in log message.
     */
    LOG_FILE_SIZE = 200,
};


#define ELEPHANTLOGGER_DEFAULT_LOGLEVEL elephantlogger::LogLevel::Debug


} // End namespace
} // End namespace
