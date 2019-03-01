#pragma once

#include "IOutput.h"

#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/core/LogMessage.h"

#include <string>

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#else
#   include <iostream>
#endif


namespace elephantlogger {


/**
 * IOutput implementation for Visual Studio Console.
 * Print message using VS console.
 *
 * \note
 * If VS not supported (Ex: Linux), use std::cout instead.
 */
class ConsoleVS : public IOutput {

    public:

        /** \copydoc IOutput::write() */
        void write(const LogMessage & message) override {
#           if defined(_WIN32) || defined(_WIN64)
                std::string msg = message.getFormattedMessage() + "\n";
                OutputDebugStringA(static_cast<LPCSTR>(msg.c_str()));
#           else
                std::cout << message.getFormattedMessage() << std::endl;
#           endif
        }
};


} // End namespace

