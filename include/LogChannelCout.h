#pragma once
#include "LogChannel.h"
#include <string>
#include <iostream>


namespace ElephantLogger {


/**
 * LogChannel implementation for std::cout output.
 */
class LogChannelCout : public LogChannel {
    public:
        LogChannelCout() = default;
        LogChannelCout(std::string const& filePath) : LogChannel(filePath) {};

    public:
        void writeInChannel(std::string const& message) const override {
            std::cout << message << std::endl;
        }
};


} // End namespace