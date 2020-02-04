// Example of categories filter at the logger level (outputs have their own filters)

#include <iostream>
#include <string>
#include <elephantlogger/log.h>
#include <elephantlogger/outputs/ConsoleOutput.h>

// Categories
static elephantlogger::LogCategory general = elephantlogger::defaultCategory; 
 static elephantlogger::LogCategory engine = 2;
static elephantlogger::LogCategory gameplay = 4;
static elephantlogger::LogCategory online = 8;

static elephantlogger::ConsoleOutput console;


void printRandomLogs() {
    LOG_INFO("Some info log (default category)");
    LOG_INFO_IN(engine, "Some info log (engine)");
    LOG_INFO_IN(gameplay, "Some info log (gameplay)");    LOG_INFO_IN(online, "Some info log (online)");
}

int main(int argc, char** argv) {
    //elephantlogger::init(); // We don't use the default config

    // Create an output that accept all categories
    elephantlogger::addOutput(&console, elephantlogger::LogLevel::Debug, elephantlogger::allCategories);

    // -------------------------------------------------------------------------
    std::cout << "--- Default with all accepted ---" << std::endl;
    printRandomLogs(); // All logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Disable all categories ---" << std::endl;
    elephantlogger::setCategoriesFilter(elephantlogger::noCategories);
    printRandomLogs(); // No logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Allow all categories ---" << std::endl;
    elephantlogger::enableAllCategories();
    printRandomLogs(); // All logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Disable default category ---" << std::endl;
    elephantlogger::disableCategories(general);
    printRandomLogs(); // General no longer displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Enable default category ---" << std::endl;
    elephantlogger::enableCategories(general);
    printRandomLogs(); // General displayed again

    // -------------------------------------------------------------------------
    std::cout << "--- Disable engine and gameplay ---" << std::endl;
    elephantlogger::disableCategories(engine + gameplay);
    printRandomLogs(); // Engine and gameplay no longer displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Re-enable engine and gameplay ---" << std::endl;
    elephantlogger::enableCategories(engine + gameplay);
    printRandomLogs(); // Engine and gameplay no longer displayed


    return 0;
}
