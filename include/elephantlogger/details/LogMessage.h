#pragma once

#include <ctime>
#include <string>
#include <cstring>
#include <stdarg.h>

#include "LogLevel.h"
#include "config.h"


namespace elephantlogger {

/**
 * Internal representation of a log message.
 * A message can't excess a defined size. (Usually 256 characters).
 */
class LogMessage {

    private:

        const LogLevel      m_logLevel;
        const int           m_channelID;
        char                m_file[config::LOG_FILE_SIZE];
        const int           m_line;
        char                m_function[config::LOG_FUNCTION_SIZE];
        char                m_message[config::LOG_MSG_SIZE];
        const std::time_t   m_creationTime;


    public:

        LogMessage(const LogLevel logLevel,
                   const int channelID,
                   const char* file,
                   const int line,
                   const char* function,
                   const char* format,
                   va_list argList) : m_logLevel(logLevel),
                                      m_channelID(channelID),
                                      m_line(line),
                                      m_creationTime(std::time(nullptr)) {
            memcpy(m_file, file, strlen(file));
            memcpy(m_function, function, strlen(function));
            vsnprintf(m_message, config::LOG_MSG_SIZE-1, format, argList); // -1 for '\0'
            m_message[config::LOG_MSG_SIZE-1] = '\0';
        }

        /**
         * Returns the formatted version of the message.
         * Message is truncated if length higher than max size.
         *
         * \return Formatted version of the message.
         */
        const std::string getFormattedMessage() const {

            std::string dateStr = ctime(&m_creationTime);
            dateStr.pop_back(); // Remove line return

            std::string msg = "[" + dateStr +"] ";
            msg += "[";
            msg += logLevelToString(m_logLevel);
            msg += "]: ";
            msg += m_message;
            return msg;
        }

        /**
         * Returns channel ID where to write this message.
         *
         * \return Channel ID.
         */
        const int getChannelID() const { return m_channelID; }
};


} // End namespace

