#pragma once

#include <ctime>
#include <string>
#include <stdarg.h> // va_list

#include "LogLevel.h"
#include "config.h"


namespace elephantlogger {



/**
 * Internal representation of a log message.
 * A message can't excess a defined size. (Usually 256 characters).
 */
class LogMessage {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    private:
        const LogLevel      m_logLevel;
        const int           m_channelID;
        char                m_file[config::LOG_FILE_SIZE];
        const int           m_line;
        char                m_function[config::LOG_FUNCTION_SIZE];
        char                m_message[config::LOG_MSG_SIZE];
        const std::time_t   m_creationTime;


    // -------------------------------------------------------------------------
    // Initialization
    // -------------------------------------------------------------------------
    public:
        LogMessage(const LogLevel logLevel,
                   const int channelID,
                   const char* file,
                   const int line,
                   const char* function,
                   const char* format,
                   va_list argList);


    // -------------------------------------------------------------------------
    // Core
    // -------------------------------------------------------------------------
    public:

        /**
         * Returns the Formatted version of the message.
         * Message is truncated if length higher than max size.
         *
         * \return Formatted version of the message.
         */
        const std::string getFormattedMessage() const;

        /**
         * Returns channel ID where to write this message.
         *
         * \return Channel ID.
         */
        const int getChannelID() const;
};


} // End namespace


