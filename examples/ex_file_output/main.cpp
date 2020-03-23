// Example that uses a custom file output configuration (but no category filters).

#include <string>
#include <elephantlogger/log.h>
#include <elephantlogger/outputs/FileLogOutput.h>

// Initialize the logger with custom outputs and categories.
static void elephant_customInit() {
    static elephantlogger::FileLogOutput filelog("elephant.log");

    elephantlogger::init();
    elephantlogger::addOutput(&filelog, elephantlogger::LogLevel::Debug);
}

int main(int argc, char** argv) {
    elephant_customInit();

    LOG_WARNING("Some warning log");
    LOG_DEBUG("Some debug log");
    LOG_ERROR("Some error log");
    LOG_CONFIG("Some config log");
    LOG_TRACE("Some trace log");
    LOG_INFO("Some information log");

    return 0;
}