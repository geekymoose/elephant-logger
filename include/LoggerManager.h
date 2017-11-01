#pragma once

#include "helper/Singleton.h"
#include "LogOutput.h"
#include "LogOutputType.h"
#include "LogMessage.h"
#include "LogLevel.h"

#include <vector>
#include <mutex>
#include <atomic>
#include <memory>
#include <thread>


namespace ElephantLogger {


/**
 * The Logger Manager (Singleton).
 * Run inside it's own thread (all functions are thread safe).
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct, 2017
 */
class LoggerManager : private Singleton<LoggerManager> {

    // -------------------------------------------------------------------------
    // Attributs
    // -------------------------------------------------------------------------
    private:

        /** True if this Logger is Running. */
        std::atomic_bool m_isRunning;

        /** The current used log level (From LogLevel enum). */
        std::atomic<std::int8_t> m_currentLogLevel; // atomic_int8_t

        /** If true, all logs are also written in files. */
        std::atomic_bool m_isLogingInFile;

        /** Path to the folder with logs. */
        std::string m_logFilePath;

        /** Path to the folder with saved logs. */
        std::string m_logFileSavePath;

        /** Lookup array of all registered and available output channels. */
        std::unique_ptr<LogOutput> m_lookupChannels[static_cast<size_t>(LogOutputType::SIZE)];

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
        friend Singleton<LoggerManager>;
        LoggerManager() = default;
        ~LoggerManager() = default;

    public:
        using Singleton<LoggerManager>::getInstance;
        void initialize() override;
        void destroy() override;


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
         * \param output    Output to use with this message.
         * \param message   The row message to display.
         * \param file      File that created the log
         * \param line      Line position in file.
         */
        void queueLog(LogLevel const level,
                      LogOutputType const output,
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
         * (Not thread safe, to use internally only).
         */
        void internalQueueLog(LogLevel level,
                              LogOutputType output,
                              std::string message,
                              std::string file,
                              const int line);

        /**
         * Process each elements from the back queue and clear it.
         */
        void internalProcessBackQueue();

        /**
         * Swap front and back queue buffers.
         */
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

        /** Logs are no longer put in files. */
        void disableLogInFile();

        /** Logs are put in files. (Use log file path currently set). */
        void enableLogInFile();

}; // End LoggerManager


} // End namespace
