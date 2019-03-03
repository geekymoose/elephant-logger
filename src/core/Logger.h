#pragma once

#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <memory>   // unique_ptr
#include <cstdarg>  // va_list

#include "../utils/Singleton.h"
#include "Channel.h"
#include "elephantlogger/core/LogLevel.h"
#include "elephantlogger/core/LogMessage.h"
#include "elephantlogger/core/config.h"


namespace elephantlogger {

class IOutput;


/**
 * The Famous Ugly Logger (Singleton).
 *
 * Run inside it's own thread (all functions are thread safe).
 * The user thread only queue message to be processed.
 */
class Logger : private Singleton<Logger> {
    ELEPHANTLOGGER_MAKE_SINGLETON(Logger);

    // -------------------------------------------------------------------------
    // Attributs
    // -------------------------------------------------------------------------
    private:
        std::atomic_int m_currentLogLevel;
        std::atomic_bool m_isRunning;
        Channel m_lookupChannels[static_cast<size_t>(config::NB_CHANNELS)];

        std::vector<LogMessage> m_queueLogs1;
        std::vector<LogMessage> m_queueLogs2;

        std::vector<LogMessage> * m_queueLogsFront = &m_queueLogs1;
        std::vector<LogMessage> * m_queueLogsBack = &m_queueLogs2;;

        std::mutex m_queuesFrontAccessMutex;
        std::mutex m_queuesBackAccessMutex;


    // -------------------------------------------------------------------------
    // Initialization / Constructors
    // -------------------------------------------------------------------------
    public:
        Logger(const LogLevel loglevel);

        /**
         * Start running this logger.
         * Do nothing if already running.
         */
        void startup();

        /**
         * Stop running this logger.
         * Cleanup queues and stop running logger.
         * Logs are no more queued.
         */
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


    // -------------------------------------------------------------------------
    // Internal Methods
    // -------------------------------------------------------------------------
    private:

        /** Process each elements from the back queue, then clear it. */
        void processBackQueue();

        /** Swap front and back queue buffers. */
        void swapQueues();

        /** Start logger loop in a thread. */
        void startBackThread();


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:

        /**
         * Check wether the given loglevel value is accepted by this logger.
         *
         * \return True if accepted, otherwise, return false.
         */
        bool isLogLevelAccepted(const LogLevel level) const;

        /**
         * Add an ouptut to a specific channel.
         * Keep a pointer to this output (Beware with variable scope).
         *
         * \param channelID The channel where to add output.
         * \param output The output to add in the channel.
         */
        void addOutput(const int channelID, IOutput * output);

        /**
         * Changes the current log level.
         */
        void setLogLevel(const LogLevel level);

        /**
         * Returns the current log level.
         */
        LogLevel getLogLevel() const;

}; // End Logger class


} // End namespace

