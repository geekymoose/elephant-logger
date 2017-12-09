#pragma once

#include "IOutput.h"


namespace elephantlogger {

class LogMessage;


/**
 * IOutput implementation for cout console.
 * Simply print in std::cout.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct 2017
 */
class ConsoleCout : public IOutput {

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


