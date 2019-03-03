#pragma once

#include <iostream>

#include "IOutput.h"
#include "elephantlogger/core/LogMessage.h"


namespace elephantlogger {


/**
 * This output writes logs in the cout console.
 */
class ConsoleOutput : public IOutput {

    public:

        /** \copydoc IOutput::write */
        void write(const LogMessage & message) override {
            std::cout << message.getFormattedMessage() << std::endl;
        }
};


} // End namespace

