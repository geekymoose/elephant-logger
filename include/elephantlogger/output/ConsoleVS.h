#pragma once

#include "IOutput.h"
#include "elephantlogger/logger/LogMessage.h"

#include <string>

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#else
#   include <iostream>
#endif


namespace elephant {


/**
 * A debug console that print on Visual Studio output.
 *
 * \note
 * If VS not supported (Ex: Linux), use std::cout instead.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Oct 2017
 */
class ConsoleVS : public IOutput {

    public:
        /**
         * \copydoc IOutput::write()
         */
        void write(const LogMessage & message) override {
#           if defined(_WIN32) || defined(_WIN64)
                std::string msg = message.getFormattedMessage() + "\n";
                OutputDebugStringA(static_cast<LPCSTR>(msg.c_str()));
#           else
                std::cout << message.getFormattedMessage() << std::endl;
#           endif
        }

        /**
         * \copydoc IOutput::flush()
         */
        void flush() override {
#           if defined(_WIN32) || defined(_WIN64)
                // A way to flush VS Console?
#           else
                std::cout << std::flush;
#           endif
        }

        /**
         * \copydoc IOutput::save()
         */
        bool save() const override {
            // Nothing to do>
            return true;
        }

        /**
         * \copydoc IOutput::clear()
         */
        void clear() override {
            // TODO
        }
};


} // End namespace
