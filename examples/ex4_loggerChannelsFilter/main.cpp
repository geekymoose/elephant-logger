// Example of channels filter at the logger level (outputs have their own filters)

#include <iostream>
#include <string>
#include <elephantlogger/log.h>
#include <elephantlogger/outputs/ConsoleOutput.h>

// Channels
static elephantlogger::LogChannel general = elephantlogger::defaultChannel; 
 static elephantlogger::LogChannel engine = 2;
static elephantlogger::LogChannel gameplay = 4;
static elephantlogger::LogChannel online = 8;

static elephantlogger::ConsoleOutput console;


void printRandomLogs() {
    LOG_INFO("Some info log (default channel)");
    LOG_INFO_IN(engine, "Some info log (engine)");
    LOG_INFO_IN(gameplay, "Some info log (gameplay)");
    LOG_INFO_IN(online, "Some info log (online)");
}

int main(int argc, char** argv) {
    //elephantlogger::init(); // We don't use the default config

    // Create an output that accept all channels
    elephantlogger::addOutput(&console, elephantlogger::LogLevel::Debug, elephantlogger::allChannels);

    // -------------------------------------------------------------------------
    std::cout << "--- Default with all accepted ---" << std::endl;
    printRandomLogs(); // All logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Disable all channels ---" << std::endl;
    elephantlogger::setChannelsFilter(elephantlogger::noChannels);
    printRandomLogs(); // No logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Allow all channels ---" << std::endl;
    elephantlogger::enableAllChannels();
    printRandomLogs(); // All logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Disable default channel ---" << std::endl;
    elephantlogger::disableChannels(general);
    printRandomLogs(); // General no longer displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Enable default channel ---" << std::endl;
    elephantlogger::enableChannels(general);
    printRandomLogs(); // General displayed again

    // -------------------------------------------------------------------------
    std::cout << "--- Disable engine and gameplay ---" << std::endl;
    elephantlogger::disableChannels(engine + gameplay);
    printRandomLogs(); // Engine and gameplay no longer displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Re-enable engine and gameplay ---" << std::endl;
    elephantlogger::enableChannels(engine + gameplay);
    printRandomLogs(); // Engine and gameplay no longer displayed


    return 0;
}
