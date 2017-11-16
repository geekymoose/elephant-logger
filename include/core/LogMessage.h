#pragma once

#include "LogLevel.h"

#include <ctime>
#include <string>


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
        LogLevel            m_logLevel;
        int                 m_channelID;
        std::string         m_message;

        const std::string   m_filePosition;
        const int           m_linePosition;
        const std::time_t   m_creationTime;


    // -------------------------------------------------------------------------
    // Init
    // -------------------------------------------------------------------------
    public:
        LogMessage(const LogLevel logLevel,
                   const int channelID,
                   std::string&& message,
                   std::string&& file,
                   const int line);


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
