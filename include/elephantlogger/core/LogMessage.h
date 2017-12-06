#pragma once

#include "LogLevel.h"

#include <ctime>
#include <string>
#include <stdarg.h> // va_list


#define LOG_MSG_SIZE        256     // Max size of displayed msg.
#define LOG_FUNCTION_SIZE   50      // Max size of displayed function name.
#define LOG_FILE_SIZE       200     // Max size of displayed file.


namespace elephantlogger {



/**
 * Internal representation of a log message.
 * A message can't excess a defined size. (Usually 256 characters).
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct, 2017
 */
class LogMessage {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    private:
        const LogLevel      m_logLevel;
        const int           m_channelID;
        char                m_file[LOG_FILE_SIZE];
        const int           m_line;
        char                m_function[LOG_FUNCTION_SIZE];
        char                m_message[LOG_MSG_SIZE];
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


