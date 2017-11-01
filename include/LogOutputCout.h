#pragma once

#include "LogOutput.h"

#include <string>
#include <iostream>


namespace ElephantLogger {


/**
 * A Debug console that print on std::cout.
 *
 * \author  Constantin Masson
 * \since   1.0
 */
class LogOutputCout : public LogOutput {
    public:
        LogOutputCout() = default;
        LogOutputCout(std::string const& filePath) : LogOutput(filePath) {};

    public:
        void print(std::string const& message) const override {
            std::cout << message << std::endl;
        }
};


} // End namespace
