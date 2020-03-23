// Example of categories filter at the logger level (outputs have their own filters)

#include <elephantlogger/log.h>
#include <iostream>
#include <string>

struct LOG_CATEGORY
{
  public:
    static const elephantlogger::LogCategory DEFAULT = elephantlogger::LOG_CATEGORY_DEFAULT;
    static const elephantlogger::LogCategory ENGINE = 2;
    static const elephantlogger::LogCategory GAMEPLAY = 3;
    static const elephantlogger::LogCategory ONLINE = 4;
};

void printRandomLogs()
{
    LOG_INFO("Some info log (Default)");
    LOG_INFO_IN(LOG_CATEGORY::ENGINE, "Some info log (Engine)");
    LOG_INFO_IN(LOG_CATEGORY::GAMEPLAY, "Some info log (Gameplay)");
    LOG_INFO_IN(LOG_CATEGORY::ONLINE, "Some info log (Online)");
}

int main(int argc, char** argv)
{
    elephantlogger::init();

    // -------------------------------------------------------------------------
    std::cout << "--- Default with all accepted ---" << std::endl;
    printRandomLogs(); // All logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Disable all categories ---" << std::endl;
    elephantlogger::disableAllCategoriesLogger();
    printRandomLogs(); // No logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Allow all categories ---" << std::endl;
    elephantlogger::enableAllCategoriesLogger();
    printRandomLogs(); // All logs displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Disable default category ---" << std::endl;
    elephantlogger::disableCategoryLogger(LOG_CATEGORY::DEFAULT);
    printRandomLogs(); // General no longer displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Enable default category ---" << std::endl;
    elephantlogger::enableCategoryLogger(LOG_CATEGORY::DEFAULT);
    printRandomLogs(); // General displayed again

    // -------------------------------------------------------------------------
    std::cout << "--- Disable engine and gameplay ---" << std::endl;
    elephantlogger::disableCategoryLogger(LOG_CATEGORY::ENGINE);
    elephantlogger::disableCategoryLogger(LOG_CATEGORY::GAMEPLAY);
    printRandomLogs(); // Engine and gameplay no longer displayed

    // -------------------------------------------------------------------------
    std::cout << "--- Re-enable engine and gameplay ---" << std::endl;
    elephantlogger::enableCategoryLogger(LOG_CATEGORY::ENGINE);
    elephantlogger::enableCategoryLogger(LOG_CATEGORY::GAMEPLAY);
    printRandomLogs(); // Engine and gameplay no longer displayed

    return 0;
}
