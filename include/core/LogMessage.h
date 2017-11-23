#pragma once

#include "LogLevel.h"

#include <ctime>
#include <string>
#include <stdarg.h> // va_list


namespace ElephantLogger {



/**
 * Internal representation of a log message.
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
        char                m_file[256];
        const int           m_line;
        char                m_function[256];
        char                m_message[256];
        const std::time_t   m_creationTime;


    // -------------------------------------------------------------------------
    // Init
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
         * (Message is truncated if length highter than max size).
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
