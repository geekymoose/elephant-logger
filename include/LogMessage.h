#pragma once

#include "LogLevel.h"
#include "LogOutputType.h"

#include <ctime>
#include <string>


namespace ElephantLogger {


/**
 * Internal representation of a log message.
 * A log message is to be printed in a specific output.
 *
 * \remark
 * LogLevel add a specific format.
 *
 * \author  Constantin Masson
 * \since   1.0
 */
class LogMessage {

    private:
        LogLevel            m_logLevel;
        LogOutputType       m_outputType;
        std::string         m_message;

        const std::string   m_filePosition;
        const int           m_linePosition;
        const std::time_t   m_creationTime;


    public:
        LogMessage(const LogLevel logLevel,
                   const LogOutputType outputType,
                   std::string&& message,
                   std::string&& file,
                   const int line);


    public:

        /**
         * Returns the Formatted version of the message.
         * (Message is truncated if length highter than max size).
         *
         * \return Formatted version of the message.
         */
        const std::string getFormattedMessage() const;

        /**
         * Gets the Output Type associated.
         *
         *\return LogOutput.
         */
        const LogOutputType getLogOutput() const;
};


} // End namespace
