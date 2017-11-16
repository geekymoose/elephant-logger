#pragma once

#include <fstream>


namespace ElephantLogger {
class LogMessage;


/**
 * Abstract class that defines where to print a log.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct 2017
 */
class IOutput {

    protected:
        IOutput() = default;

    public:
        virtual ~IOutput() = default;


    public:

        /**
         * Write a message on this output and add a line return.
         * Special format may be added.
         *
         * \param message The message to print in the channel.
         */
        virtual void write(const LogMessage & message) = 0;

        /**
         * Flush output now.
         */
        virtual void flush() = 0;
};


} // End namespace
