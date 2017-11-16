#pragma once

#include "IOutput.h"

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#else
#   include <iostream>
#endif


namespace ElephantLogger {


/**
 * A debug console that print on Visual Studio output.
 * If VS not supported (Ex: Linux), use std::cout instead.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct 2017
 */
class ConsoleVS : public IOutput {
    public:
        void write(const LogMessage & message) override {
#           if defined(_WIN32) || defined(_WIN64)
                //OutputDebugStringA(static_cast<LPCSTR>(message.c_str()));
                //OutputDebugStringA(static_cast<LPCSTR>("\n"));
                // (There is probably a cleaner way to return line)
                // TODO
#           else
                //std::cout << message << std::endl;
                // TODO
#           endif
        }
};


} // End namespace
