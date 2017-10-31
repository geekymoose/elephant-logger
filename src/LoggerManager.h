#pragma once

#include "MoonSingleton.h"
#include "LogChannel.h"
#include "LogMessage.h"
#include "LogLevel.h"

#include <vector>


namespace MoonRPG
{


    // -------------------------------------------------------------------------
    // LOG MANAGER
    // -------------------------------------------------------------------------

    /**
     * The main logger manager (Singleton).
     * All functions are thread safe.
     *
     * \remark
     * By default, logs are only displayed in channels.
     * logInFileMode may be set to also write all logs in files.
     * 
     * \remark
     * Log level may be set to choose which logs are bypassed.
     * Only logs with lower or equal enum value are displayed.
     * (See LogLevel Enum).
     *
     * \author  Constantin Masson
     * \date    Oct, 2017
     */
    class LoggerManager : private MoonSingleton<LoggerManager>
    {

        private:
            // -----------------------------------------------------------------
            // Attributs
            // -----------------------------------------------------------------

            /** True if this Logger is Running */
            std::atomic_bool m_isRunning;

            /** The current used log level (From LogLevel enum). */
            std::atomic_int8_t m_currentLogLevel; // LogLevel type

            /** If true, all logs are also written in files. */
            std::atomic_bool m_isLogingInFile;

            /** Path to the folder with logs. */
            std::string m_logFilePath;

            /** Path to the folder with saved logs. */
            std::string m_logFileSavePath;

            /** Lookup array of all registered and available output channels. */
            std::unique_ptr<LogChannel> m_lookupChannels[static_cast<size_t>(LogLevel::LogLevelSize)];

            /** Vector of logs */
            std::vector<LogMessage>		m_queueLogs1;
            std::vector<LogMessage>		m_queueLogs2;

            /** Point to the vector where logs are queued. */
            std::vector<LogMessage>*	m_queueLogsFront;

            /** Point to the vector currently processed by the Logger. */
            std::vector<LogMessage>*	m_queueLogsBack;

            /** Mutex for Front log queues access */
            std::mutex m_queuesFrontAccessMutex;


        private:
            // -----------------------------------------------------------------
            // Singleton implementation / override
            // -----------------------------------------------------------------
            GENERATE_CODE_FROM_MoonSingleton(LoggerManager);

        public:
            void initialize() override;
            void destroy() override;


        public:
            // -----------------------------------------------------------------
            // Core End User Methods
            // -----------------------------------------------------------------

            /**
             * Queue a Log if level is accepted by current Log settings.
             * Log is queued to be written in the respective LogChannel.
             * Current loggerManager level is used to bypass logs with superior
             * level (Less critical logs) than current level.
             *
             * \remark
             * This function is thread safe and may be called concurrently.
             *
             * \param level     Log Level for this message.
             * \param output    Channel to use with this message.
             * \param message   The row message to display.
             */
            void queueLog(LogLevel const level, LogChannel::Output const output,
                          char const* message,
                          char const* file,
                          const int line);

            /**
             * Save all current log files in the save directory set.
             * This process a simple copy of current log file path to save path.
             * Do nothing if log in file is not allowed (False returned).
             *
             * \return True if successfully saved, otherwise, return false.
             */
            bool saveAllLogFiles() const;


        private:
            // -----------------------------------------------------------------
            // Internal methods
            // -----------------------------------------------------------------

            /**
             * Queue a log, regardless any settings.
             */
            void internalQueueLog(LogLevel level, LogChannel::Output output,
                                  std::string message,
                                  std::string file,
                                  const int line);

            /**
             * Run the LoggerEngine in a new thread.
             * LoggerEngine can be started only if it's not already running.
             */
            void internalStartLoggerThread();

            /**
             * Process each elements from the back queue and clear it.
             */
            void internalProcessBackQueue();

            /**
             * Swap front and back queue buffers.
             */
            void internalSwapQueues();

        public:
            // -----------------------------------------------------------------
            // Getters - Setters
            // -----------------------------------------------------------------

            /** Changes the current log level. */
            void setLogLevel(const LogLevel level);

            /** Returns the current log level. */
            LogLevel getLogLevel() const;

            /** Logs are no longer put in files. */
            void disableLogInFile();

            /** Logs are put in files. (Use log file path currently set). */
            void enableLogInFile();

    }; // End LoggerManager


} // End MoonRPG Namespace