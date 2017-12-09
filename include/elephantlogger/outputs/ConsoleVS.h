#pragma once

#include "IOutput.h"


namespace elephantlogger {

class LogMessage;


/**
 * IOutput implementation for Visual Studio Console.
 * Print message using VS console.
 *
 * \note
 * If VS not supported (Ex: Linux), use std::cout instead.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct 2017
 */
class ConsoleVS : public IOutput {

    public:
        /**
         * \copydoc IOutput::write()
         */
        void write(const LogMessage & message) override;

        /**
         * \copydoc IOutput::save(const char*)
         */
        bool save(const char* path) const override;

        /**
         * \copydoc IOutput::flush()
         */
        void flush() override;

        /**
         * \copydoc IOutput::clear()
         */
        void clear() override;
};


} // End namespace
