#pragma once
#include "LogChannel.h"

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#else
#   include <iostream>
#endif


namespace ElephantLogger {


/**
 * LogChannel implementation for Visual Studio output.
 * If VS not supported, use std::cout instead.
 */
class LogChannelVS : public LogChannel {
    public:
        LogChannelVS() = default;
        LogChannelVS(std::string const& filePath) : LogChannel(filePath) {};

    public:
        void writeInChannel(std::string const& message) const override {
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
