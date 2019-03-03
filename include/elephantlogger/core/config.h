#pragma once


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

    /**
     * Time between two queue processing and swap.
     * This is used to slow down logger thread,
     * otherwise, thread would probably use too many resources.
     */
    THREAD_UPDATE_RATE = 250,

    /**
     * Max number of available channels.
     */
    NB_CHANNELS = 5,

    /**
     * Initial size of the log queue.
     *
     * Each time a message is queued, I use push_back,
     * which is slow if has reached vector max size.
     * To avoid this, we should initialize the queue with a size big enough
     * to be hard to reach (Not enough logs in the queue)
     * and small enough for memory use space.
     */
    DEFAULT_QUEUE_SIZE = 40,

    /**
     * Default log level used when logger is created.
     */
    DEFAULT_LOGLEVEL = static_cast<int>(elephantlogger::LogLevel::Debug)
};


} // End namespace
} // End namespace
