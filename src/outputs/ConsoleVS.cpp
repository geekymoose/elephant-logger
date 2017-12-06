#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/core/LogMessage.h"

#include <string>

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#else
#   include <iostream>
#endif


using namespace elephantlogger;


#if defined(_WIN32) || defined(_WIN64)

    void ConsoleVS::write(const LogMessage & message) {
        std::string msg = message.getFormattedMessage() + "\n";
        OutputDebugStringA(static_cast<LPCSTR>(msg.c_str()));
    }

    void ConsoleVS::flush() {
        // A way to flush VS Console?
    }

#else

    void ConsoleVS::write(const LogMessage & message) {
        std::cout << message.getFormattedMessage() << std::endl;
    }

    void ConsoleVS::flush() {
        std::cout << std::flush;
    }

#endif


bool ConsoleVS::save() const {
    // Nothing to do>
    return true;
}

void ConsoleVS::clear() {
    // TODO
}
