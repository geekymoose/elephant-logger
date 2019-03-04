// Example that uses custom configuration.

#include <string>
#include <elephantlogger/log.h>

// Include Outputs headers
#include <elephantlogger/outputs/DebugOutput.h>
#include <elephantlogger/outputs/FileOutput.h>


// Initialize the logger with custom outputs and channels.
static void customInitElephant() {
    static elephantlogger::DebugOutput      debugOutput;
    static elephantlogger::FileOutput       filelog("elephant.log");

    elephantlogger::init();

    elephantlogger::addOutput(1, &debugOutput);
    elephantlogger::addOutput(1, &filelog);
}

int main(int argc, char** argv) {
    customInitElephant();

    LOG_WARNING_(1, "Some warning log");
    LOG_DEBUG_(1, "Some debug log");
    LOG_ERROR_(1, "Some error log");
    LOG_CONFIG_(1, "Some config log");
    LOG_TRACE_(1, "Some trace log");
    LOG_INFO_(1, "Some information log");
    return 0;
}
