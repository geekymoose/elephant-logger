#pragma once

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#else
#   include <iostream>
#endif

#include "IOutput.h"


namespace elephantlogger {


/**
 * Writes logs in the console.
 * Uses VS console on Windows, otherwise, uses std::cout.
 */
class ConsoleOutput : public IOutput {

    public:

        /** \copydoc IOutput::write() */
        void write(const LogMessage & message) override {
#if defined(_WIN32) || defined(_WIN64)
            std::string msg = message.getFormattedMessage() + "\n";
            OutputDebugStringA(static_cast<LPCSTR>(msg.c_str()));
#else
            std::cout << message.getFormattedMessage() << std::endl;
#endif
        }
};


}

