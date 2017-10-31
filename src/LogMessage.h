#pragma once

#include "LogLevel.h"
#include "LogChannel.h"

#include <ctime>

namespace MoonRPG
{


    /**
     * Internal representation of a log message.
     * A log message is to be printed in a specific channel.
     * It has a message and a LogLevel.
     * LogLevel add specific format.
     */
    class LogMessage {

        private:
            LogLevel				m_logLevel;
            LogChannel::Output		m_channel;
            std::string		        m_message;

            const std::string       m_filePosition;
            const int               m_linePosition;
            const std::time_t       m_creationTime;


        public:
            LogMessage(const LogLevel logLevel,
                       const LogChannel::Output channel,
                       std::string&& message,
                       std::string&& file,
                       const int line);


        public:

            /**
             * Returns the Formatted version of the message.
             * (Message is truncated if length highter than max size).
             *
             * \warning
             * Not thread safe, only one formatedMessage can be set (Static variable).
             *
             * \return Pointer to the static variable that has the formated message.
             */
            const std::string getFormattedMessage() const;

            /**
             * Returns the logChannel associated with this LogMessage.
             */
            const LogChannel::Output getLogChannel() const;
    };


} // End namespace