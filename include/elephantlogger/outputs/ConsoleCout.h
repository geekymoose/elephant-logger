#pragma once

#include "IOutput.h"
#include "elephantlogger/core/LogMessage.h"

#include <iostream>



namespace elephantlogger {


/**
 * IOutput implementation for cout console.
 * Simply print in std::cout.
 */
class ConsoleCout : public IOutput {

    public:

        /** \copydoc IOutput::write */
        void write(const LogMessage & message) override {
            std::cout << message.getFormattedMessage() << std::endl;
        }
};


} // End namespace

