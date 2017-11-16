#pragma once

#include "IOutput.h"

#include <string>
#include <iostream>


namespace ElephantLogger {


/**
 * A Debug console that print on std::cout.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct 2017
 */
class ConsoleCout : public IOutput {
    public:
        void write(const LogMessage & message) override {
            //std::cout << message << std::endl;
            // TODO
        }
};


} // End namespace
