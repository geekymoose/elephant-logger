#pragma once

#include "LogOutput.h"

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
 */
class LogOutputVS : public LogOutput {
    public:
        LogOutputVS() = default;
        LogOutputVS(std::string const& filePath) : LogOutput(filePath) {};

    public:
        void print(std::string const& message) const override {
#           if defined(_WIN32) || defined(_WIN64)
                OutputDebugStringA(static_cast<LPCSTR>(message.c_str()));
                OutputDebugStringA(static_cast<LPCSTR>("\n"));
                // (There is probably a cleaner way to return line)
#           else
                std::cout << message << std::endl;
#           endif
        }
};


} // End namespace
