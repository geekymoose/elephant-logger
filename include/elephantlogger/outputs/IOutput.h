#pragma once

#include <fstream>


namespace elephantlogger {

class LogMessage;


/**
 * Interface that defines how to print a log.
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
         * Save output in a safe place.
         *
         * \param path Path where to save.
         * \return True if successfully saved, otherwise, return false.
         */
        virtual bool save(const char* path) const = 0;

        /**
         * Flush output content.
         */
        virtual void flush() = 0;

        /**
         * Clear output content.
         */
        virtual void clear() = 0;
};


} // End namespace


