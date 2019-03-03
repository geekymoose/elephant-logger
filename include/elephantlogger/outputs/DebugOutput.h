#pragma once

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#else
#   include <iostream>
#endif

#include "IOutput.h"
#include "elephantlogger/core/LogMessage.h"


namespace elephantlogger {


/**
 * This output writes logs in the debug.
 * Uses VS console on Windows, otherwise, uses std::clog.
 */
class DebugOutput : public IOutput {

    public:

        /** \copydoc IOutput::write() */
        void write(const LogMessage & message) override {
#if defined(_WIN32) || defined(_WIN64)
            std::string msg = message.getFormattedMessage() + "\n";
            OutputDebugStringA(static_cast<LPCSTR>(msg.c_str()));
#else
            std::clog << message.getFormattedMessage() << std::endl;
#endif
        }
};


} // End namespace

