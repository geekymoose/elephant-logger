// Example that uses custom configuration.

#include <string>
#include <elephantlogger/log.h>
#include <elephantlogger/outputs/ConsoleLogOutput.h>
#include <elephantlogger/outputs/FileLogOutput.h>

// Categories accessible from the code
static uint64_t CATEGORY_ONLINE = 1;
static uint64_t CATEGORY_ENGINE = 2;

// Initialize the logger with custom outputs and categories.
static void customInitElephant() {
    elephantlogger::init();

    static elephantlogger::ConsoleLogOutput   ConsoleLogOutput;
    static elephantlogger::FileLogOutput      filelog("elephant.log");

    elephantlogger::addOutput(&ConsoleLogOutput, elephantlogger::LogLevel::Debug, CATEGORY_ENGINE);
    elephantlogger::addOutput(&filelog, elephantlogger::LogLevel::Debug, CATEGORY_ONLINE);
}

int main(int argc, char** argv) {
    customInitElephant();

    LOG_WARNING_IN(CATEGORY_ONLINE, "Some warning log");
    LOG_DEBUG_IN(CATEGORY_ENGINE, "Some debug log");
    LOG_ERROR_IN(CATEGORY_ENGINE, "Some error log");
    LOG_CONFIG_IN(CATEGORY_ONLINE, "Some config log");
    LOG_TRACE_IN(CATEGORY_ENGINE, "Some trace log");
    LOG_INFO_IN(CATEGORY_ENGINE, "Some information log");

    return 0;
}
