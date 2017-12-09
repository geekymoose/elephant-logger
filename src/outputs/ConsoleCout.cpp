#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/core/LogMessage.h"

#include <iostream>

using namespace elephantlogger;


void ConsoleCout::write(const LogMessage & message) {
    std::cout << message.getFormattedMessage() << std::endl;
}

bool ConsoleCout::save(const char* path) const {
    // Nothing to do
    return true;
}

void ConsoleCout::flush() {
    std::cout << std::flush;
}

void ConsoleCout::clear() {
    // TODO
}
