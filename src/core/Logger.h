#pragma once

#include "Channel.h"
#include "elephantlogger/core/LogLevel.h"
#include "elephantlogger/core/LogMessage.h"

#include "../utils/Singleton.h"
#include "../utils/config.h"

#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>   // unique_ptr
#include <cstdarg>  // va_list


namespace elephantlogger {

class Channel;
class IOutput;


/**
 * The Famous Ugly Logger (Singleton).
 *
 * Run inside it's own thread (all functions are thread safe).
 * The user thread only queue message to be processed.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct, 2017
 */
class Logger : private Singleton<Logger> {

    // -------------------------------------------------------------------------
    // Attributs (Config)
    // -------------------------------------------------------------------------
    private:
        /** The current used log level (From LogLevel enum). */
        std::atomic<std::int8_t> m_currentLogLevel; // atomic_int8_t

        /** Path to the folder with logs. */
        std::string m_logFilePath;

        /** True if clear any output at start (ex: clear log file). */
        bool m_clearAtStart;


    // -------------------------------------------------------------------------
    // Attributs (Internal use: general)
    // -------------------------------------------------------------------------
    private:

        /** Lookup array of all available channels. */
        std::unique_ptr<Channel> m_lookupChannels[static_cast<size_t>(NB_CHANNELS)];

        /** True if this Logger is Running. */
        std::atomic_bool m_isRunning;

        /** Update rate. */
        int m_threadUpdateRate;

        /**
         * Initial size of the queue.
         *
         * Each time a message is queued, I use push_back,
         * which is slow if has reached vector max size.
         * To avoid this, we should initialize the queue with a size big enough
         * to be hard to reach (Not enough logs in the queue)
         * and small enough for memory use space.
         */
        int m_defaultQueueSize;


    // -------------------------------------------------------------------------
    // Attributs (Internal use: queue)
    // -------------------------------------------------------------------------
    private:

        /** Vector of logs (List 1). */
        std::vector<LogMessage> m_queueLogs1;

        /** Vector of logs (List 2). */
        std::vector<LogMessage> m_queueLogs2;

        /** Point to the vector where logs are queued. */
        std::vector<LogMessage>* m_queueLogsFront;

        /** Point to the vector currently processed by the Logger. */
        std::vector<LogMessage>* m_queueLogsBack;

        /** Mutex for Front Logs queue access. */
        std::mutex m_queuesFrontAccessMutex;


    // -------------------------------------------------------------------------
    // Initialization / Constructors
    // -------------------------------------------------------------------------
    private:
        friend Singleton<Logger>;
        Logger() = default;
        ~Logger() = default;

    public:
        using Singleton<Logger>::get;

        void startup();
        void shutdown();


    // -------------------------------------------------------------------------
    // Core Methods
    // -------------------------------------------------------------------------
    public:

        /**
         * Queue a log to be processed by the respective Output.
         * This function is meant be be as fast as possible.
         * Only queue the message to be processed later by logger thread.
         *
         * \remark
         * Log is queued regardless its log level.
         *
         * \remark
         * This function is thread safe and may be called concurrently.
         *
         * \param level     Log Level for this message.
         * \param channelID ID of the channel where to write log.
         * \param file      File that created the log
         * \param line      Line position in file.
         * \param function  Function's name.
         * \param format    Row message, using printf convention (%s, %d etc).
         * \param argList   Variable list of parameters.
         */
        void queueLog(const LogLevel level,
                      const int channelID,
                      const char* file,
                      const int line,
                      const char* function,
                      const char* format,
                      va_list argList);

        /**
         * Save all logs in a safe directory.
         */
        void saveAllLogs() const;


    // -------------------------------------------------------------------------
    // Internal Methods
    // -------------------------------------------------------------------------
    private:

        /**
         * Process each elements from the back queue and clear it.
         */
        void processBackQueue();

        /**
         * Swap front and back queue buffers.
         */
        void swapQueues();

        /**
         * Start logger loop.
         */
        void run();

        /**
         * Start logger loop in a thread.
         */
        void runInThread();


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:

        /**
         * Check wether the given loglevel value is accepted by this logger.
         *
         * \return True if accepted, otherwise, return false.
         */
        bool isAcceptedLogLevel(const LogLevel level) const;

        /**
         * Add an ouptut to a specific channel.
         * Keep a pointer to this output (Beware with variable scope).
         *
         * \param channelID The channel where to add output.
         * \param output The output to add in the channel.
         */
        void addOutput(const int channelID, IOutput* output);

        /**
         * Changes the current log level.
         */
        void setLogLevel(const LogLevel level);

        /**
         * Returns the current log level.
         */
        LogLevel getLogLevel() const;

        // TODO
        std::string getLogFilePath() const;

        // TODO
        void setLogFilePath(const char* path);

}; // End Logger class


} // End namespace


