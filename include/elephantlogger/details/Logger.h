#pragma once

#include <vector>
#include <cstdarg>

#include "elephantlogger/outputs/IOutput.h"
#include "Channel.h"
#include "LogLevel.h"
#include "LogMessage.h"
#include "config.h"
#include "utils.h"


namespace elephantlogger {

/**
 * The Famous Ugly Logger (Singleton).
 */
class Logger : private Singleton<Logger> {
    ELEPHANTLOGGER_ADD_SINGLETON_UTILS(Logger);

    private:

        LogLevel m_currentLogLevel;
        Channel m_lookupChannels[static_cast<size_t>(config::NB_CHANNELS)];

    public:

        /**
         * Queue a log to be processed by the respective Output.
         * This function is meant be be as fast as possible.
         * Only queue the message to be processed later by logger thread.
         *
         * \param level     Log Level for this message.
         * \param channelID ID of the channel where to write log.
         * \param file      File that created the log
         * \param line      Line position in file.
         * \param function  Function's name.
         * \param format    Row message, using printf convention (%s, %d etc).
         * \param argList   Variable list of parameters.
         */
        void log(const LogLevel level,
                 const int channelID,
                 const char * file,
                 const int line,
                 const char * function,
                 const char * format,
                 va_list argList) {
            LogMessage msg(level, channelID, file, line, function, format, argList);
            ELEPHANTLOGGER_ASSERT(channelID < config::NB_CHANNELS);
            if(channelID < config::NB_CHANNELS) {
                auto& coco = m_lookupChannels[static_cast<size_t>(channelID)];
                coco.write(msg);
            }
        }

        /**
         * Checks whether the given loglevel value is accepted by this logger.
         *
         * \return True if accepted, otherwise, return false.
         */
        bool isLogLevelAccepted(const LogLevel level) const {
            return m_currentLogLevel >= level;
        }

        /**
         * Adds an output to the specific channel.
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
            m_currentLogLevel = level;
        }

        /**
         * Returns the current log level.
         */
        LogLevel getLogLevel() const {
            return m_currentLogLevel;
        }

    private:

        Logger() = default;
        ~Logger() = default;
};


} // End namespace

