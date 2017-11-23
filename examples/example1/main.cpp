#include "logger/ElephantLogger.h"

#include <chrono>
#include <thread>


// A simple test
int main(int argc, char** argv) {

    ElephantLogger::init();

    LOG_WTF(0, "1. TEST ERROR");
    LOG_ERROR(0, "1. TEST ERROR");
    LOG_WARNING(0, "2. TEST WARNING");
    LOG_CONFIG(0, "3. TEST CONFIG");
    LOG_INFO(0, "4. TEST INFO");
    LOG_TRACE(0, "5. TEST TRACE");
    LOG_DEBUG(0, "6. TEST DEBUG");

    LOG_DEBUG(0, "Integer value: %d", 42);
    LOG_DEBUG(0, "Float value: %f", 31.9);
    LOG_DEBUG(0, "Bool value (true): %d", true);
    LOG_DEBUG(0, "NULL (Using d): %d", NULL);
    LOG_DEBUG(0, "NULL (Using s): %s", NULL);

    LOG_DEBUG(0, "String: %s / Integer: %d / Float: %f / Char: %c", "Hello", 2, 7.1, 'c');

    int counter = 0;
    while(true) {
        counter++;
        LOG_DEBUG(0, "Log in loop (counter: %d)", counter);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
