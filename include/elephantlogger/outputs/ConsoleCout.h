#pragma once

#include "IOutput.h"


namespace elephantlogger {

class LogMessage;


/**
 * A Debug console that print on std::cout.
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


