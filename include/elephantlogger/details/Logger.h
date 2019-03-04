#pragma once

#include <vector>
#include <mutex>
#include <atomic>
#include <thread>
#include <cstdarg>

#include "Channel.h"
#include "LogLevel.h"
#include "LogMessage.h"
#include "config.h"
#include "utils.h"


namespace elephantlogger {

class IOutput;


/**
 * The Famous Ugly Logger (Singleton).
 *
 * Run inside it's own thread (all functions are thread safe).
 * The user thread only queue message to be processed.
 */
class Logger : private Singleton<Logger> {
    ELEPHANTLOGGER_ADD_SINGLETON_UTILS(Logger);

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
    private:
        Logger() : m_isRunning(false) {}
        ~Logger() { shutdown(); }

    public:

        /**
         * Start running this logger.
         * Do nothing if already running.
         */
        void startup() {
            ELEPHANTLOGGER_ASSERT(m_isRunning == false);
            if (m_isRunning) {
                return;
            }

            m_isRunning         = true;
            m_queueLogsFront    = &m_queueLogs1;
            m_queueLogsBack     = &m_queueLogs2;
            m_queueLogs1.reserve(config::DEFAULT_QUEUE_SIZE);
            m_queueLogs2.reserve(config::DEFAULT_QUEUE_SIZE);

            ELEPHANTLOGGER_ASSERT(m_queueLogsFront != nullptr);
            ELEPHANTLOGGER_ASSERT(m_queueLogsBack  != nullptr);

            startBackThread();
        }


        /**
         * Stop running this logger.
         * Cleanup queues and stop running logger.
         * Logs are no more queued.
         */
        void shutdown() {
            m_isRunning = false;
            swapQueues();
            processBackQueue();
            swapQueues();
            processBackQueue();
        }


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
                      va_list argList) {

            std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);

            if (m_isRunning) {
                m_queueLogsFront->emplace_back(
                        level, channelID, file, line, function, format, argList);
            }
        }


    // -------------------------------------------------------------------------
    // Internal Methods
    // -------------------------------------------------------------------------
    private:

        /** Process each elements from the back queue, then clear it. */
        void processBackQueue() {
            std::lock_guard<std::mutex> lock(m_queuesBackAccessMutex);

            for (LogMessage& msg : *m_queueLogsBack) {
                int channelID = msg.getChannelID();
                ELEPHANTLOGGER_ASSERT(channelID < config::NB_CHANNELS);

                if(channelID < config::NB_CHANNELS) {
                    auto& coco = m_lookupChannels[static_cast<size_t>(channelID)];
                    coco.write(msg);
                }
            }
            m_queueLogsBack->clear();
        }

        /** Swap front and back queue buffers. */
        void swapQueues() {
            std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);
            std::lock_guard<std::mutex> lock2(m_queuesBackAccessMutex);
            std::swap(m_queueLogsFront, m_queueLogsBack);
        }

        /** Start logger loop in a thread. */
        void startBackThread() {
            std::thread {
                [this]() {
                    while (m_isRunning) {
                        // TODO this is ugly. To change with condition var for instance
                        std::this_thread::sleep_for(std::chrono::milliseconds{
                                config::THREAD_UPDATE_RATE
                        });
                        processBackQueue();
                        swapQueues();
                    }
                }
            }.detach();
        }


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:

        /**
         * Check wether the given loglevel value is accepted by this logger.
         *
         * \return True if accepted, otherwise, return false.
         */
        bool isLogLevelAccepted(const LogLevel level) const {
            return m_currentLogLevel >= level;
        }

        /**
         * Add an ouptut to a specific channel.
         * Keep a pointer to this output (Beware with variable scope).
         *
         * \param channelID The channel where to add output.
         * \param output The output to add in the channel.
         */
        void addOutput(const int channelID, IOutput * output) {
            ELEPHANTLOGGER_ASSERT(output != nullptr);
            ELEPHANTLOGGER_ASSERT(channelID >= 0 && channelID < config::NB_CHANNELS);
            if(channelID >= 0 && channelID < config::NB_CHANNELS) {
                m_lookupChannels[channelID].addOutput(output);
            }
        }

        /**
         * Changes the current log level.
         */
        void setLogLevel(const LogLevel level) {
            m_currentLogLevel = static_cast<int>(level);
        }

        /**
         * Returns the current log level.
         */
        LogLevel getLogLevel() const {
            return static_cast<LogLevel>(m_currentLogLevel.load());
        }

}; // End Logger class


} // End namespace

