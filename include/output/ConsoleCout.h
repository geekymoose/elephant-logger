#pragma once

#include "IOutput.h"
#include "logger/LogMessage.h"

#include <iostream>


namespace elephant {


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
        void write(const LogMessage & message) override {
            std::cout << message.getFormattedMessage() << std::endl;
        }

        /**
         * \copydoc IOutput::flush()
         */
        void flush() override {
            std::cout << std::flush;
        }

        /**
         * \copydoc IOutput::save()
         */
        bool save() const override {
            // Nothing to do>
            return true;
        }

        /**
         * \copydoc IOutput::clear()
         */
        void clear() override {
            // TODO
        }
};


} // End namespace


