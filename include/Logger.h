#pragma once

#include "utils/Singleton.h"
#include "core/LogLevel.h"
#include "core/Channel.h"
#include "core/LogMessage.h"

#include <vector>
#include <mutex>
#include <atomic>
#include <memory>
#include <thread>


namespace ElephantLogger {


/**
 * The Famouse Ugly Logger (Singleton).
 * Run inside it's own thread (all functions are thread safe).
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct, 2017
 */
class Logger : private Singleton<Logger> {

    // -------------------------------------------------------------------------
    // Attributs
    // -------------------------------------------------------------------------
    private:

        /** True if this Logger is Running. */
        std::atomic_bool m_isRunning;

        /** The current used log level (From LogLevel enum). */
        std::atomic<std::int8_t> m_currentLogLevel; // atomic_int8_t

        /** Path to the folder with logs. */
        std::string m_logFilePath;

        /** Lookup array of all available channels. */
        std::unique_ptr<Channel> m_lookupChannels[static_cast<size_t>(3)];

        /** Vector of logs. */
        std::vector<LogMessage> m_queueLogs1;
        std::vector<LogMessage> m_queueLogs2;

        /** Point to the vector where logs are queued. */
        std::vector<LogMessage>* m_queueLogsFront;

        /** Point to the vector currently processed by the Logger. */
        std::vector<LogMessage>* m_queueLogsBack;

        /** Mutex for FrontLogs queue access. */
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


    // -----------------------------------------------------------------
    // Core Methods
    // -----------------------------------------------------------------
    public:

        /**
         * Queue a log to be processed by the respective Output.
         *
         * \remark
         * Only logs more critical or equal to current LogLevel are queued.
         *
         * \remark
         * This function is thread safe and may be called concurrently.
         *
         * \param level     Log Level for this message.
         * \param channelID ID of the channel where to write log.
         * \param message   The row message to display.
         * \param file      File that created the log
         * \param line      Line position in file.
         */
        void queueLog(LogLevel const level,
                      const int channelID,
                      char const* message,
                      char const* file,
                      const int line);

        /**
         * Save all logs in a save directory.
         * This simply copy the logPath directory into a safe LogPath directory.
         *
         * \remark
         * Do nothing if log in file is not allowed (False returned).
         *
         * \return True if successfully saved, otherwise, return false.
         */
        bool saveAllLogFiles() const;


    // -------------------------------------------------------------------------
    // Internal Methods
    // -------------------------------------------------------------------------
    private:

        /**
         * Queue a log, regardless any settings.
         * Not thread safe, to use internally only.
         */
        void internalQueueLog(LogLevel level,
                              const int channelID,
                              std::string message,
                              std::string file,
                              const int line);

        /** Process each elements from the back queue and clear it.  */
        void internalProcessBackQueue();

        /** Swap front and back queue buffers.  */
        void internalSwapQueues();

        /**
         * Runs the LoggerEngine in a new thread.
         * LoggerEngine can be started only if it's not already running.
         */
        void internalStartLoggerThread();


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:

        /** Changes the current log level. */
        void setLogLevel(const LogLevel level);

        /** Returns the current log level. */
        LogLevel getLogLevel() const;

}; // End Logger class


} // End namespace
