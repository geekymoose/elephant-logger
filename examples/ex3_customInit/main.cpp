// Example that uses custom configuration.

#include <string>
#include <elephantlogger/log.h>
#include <elephantlogger/outputs/ConsoleOutput.h>
#include <elephantlogger/outputs/FileOutput.h>

// Channels accessible from the code
static uint64_t CHANNEL_ONLINE = 1;
static uint64_t CHANNEL_ENGINE = 2;

// Initialize the logger with custom outputs and channels.
static void customInitElephant() {
    elephantlogger::init();

    static elephantlogger::ConsoleOutput   consoleOutput;
    static elephantlogger::FileOutput      filelog("elephant.log");

    elephantlogger::addOutput(&consoleOutput, elephantlogger::LogLevel::Debug, CHANNEL_ENGINE);
    elephantlogger::addOutput(&filelog, elephantlogger::LogLevel::Debug, CHANNEL_ONLINE);
}

int main(int argc, char** argv) {
    customInitElephant();

    LOG_WARNING_(CHANNEL_ONLINE, "Some warning log");
    LOG_DEBUG_(CHANNEL_ENGINE, "Some debug log");
    LOG_ERROR_(CHANNEL_ENGINE, "Some error log");
    LOG_CONFIG_(CHANNEL_ONLINE, "Some config log");
    LOG_TRACE_(CHANNEL_ENGINE, "Some trace log");
    LOG_INFO_(CHANNEL_ENGINE, "Some information log");

    return 0;
}
