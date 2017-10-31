#pragma once
#include "LogChannel.h"
#include <windows.h>


namespace ElephantLogger {


/**
 * LogChannel implementation for Visual Studio output.
 */
class LogChannelVS : public LogChannel {
    public:
        LogChannelVS() = default;
        LogChannelVS(std::string const& filePath) : LogChannel(filePath) {};

    public:
        void writeInChannel(std::string const& message) const override {
            OutputDebugStringA(static_cast<LPCSTR>(message.c_str()));
            OutputDebugStringA(static_cast<LPCSTR>("\n")); // There is probably a cleaner way
        }
};


} // End namespace