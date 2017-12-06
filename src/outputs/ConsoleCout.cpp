#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/logger/LogMessage.h"

#include <iostream>

using namespace elephantlogger;


void ConsoleCout::write(const LogMessage & message) {
    std::cout << message.getFormattedMessage() << std::endl;
}

void ConsoleCout::flush() {
    std::cout << std::flush;
}

bool ConsoleCout::save() const {
    // Nothing to do>
    return true;
}

void ConsoleCout::clear() {
    // TODO
}

