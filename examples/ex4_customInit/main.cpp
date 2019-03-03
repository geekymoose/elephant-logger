/*
 * Example that uses custom configuration.
 */

#include <string>
#include <elephantlogger/log.h>

// Include Outputs headers
#include "elephantlogger/outputs/DebugOutput.h"
#include "elephantlogger/outputs/FileOutput.h"


// Initialize the logger with custom outputs and channels.
static void customInitElephant() {
    static elephantlogger::DebugOutput      debugOutput;
    static elephantlogger::FileOutput       filelog("elephant.log");

    elephantlogger::init();

    elephantlogger::addOutput(1, &debugOutput);
    elephantlogger::addOutput(1, &filelog);
}

void foo() {
    LOG_WARNING(1, "Some warning log");
    LOG_DEBUG(1, "Some debug log");
    LOG_ERROR(1, "Some error log");
    LOG_CONFIG(1, "Some config log");
    LOG_TRACE(1, "Some trace log");
    LOG_INFO(1, "Some information log");
}

int main(int argc, char** argv) {
    customInitElephant();

    LOG_CONFIG(0, "Start custom init example");

    foo(); // Your code

    LOG_CONFIG(0, "Stop custom init example");
    return 0;
}
