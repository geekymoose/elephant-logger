#pragma once

#include "IOutput.h"


namespace elephantlogger {

class LogMessage;


/**
 * A debug console that print on Visual Studio output.
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
         * \copydoc IOutput::flush()
         */
        void flush() override;

        /**
         * \copydoc IOutput::save()
         */
        bool save() const override;

        /**
         * \copydoc IOutput::clear()
         */
        void clear() override;
};


} // End namespace
