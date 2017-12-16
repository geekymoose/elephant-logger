/*
 * A simple example with default configuration.
 *
 * Author:  Constantin Masson
 * Date:    Nov 2017
 */

#include "elephantlogger/log.h"

#include <chrono>
#include <thread>


int main(int argc, char** argv) {

    elephantlogger::initDefault();

    LOG_WTF(0, "Log WTF");
    LOG_ERROR(0, "Log error");
    LOG_WARNING(0, "Log warning");
    LOG_CONFIG(0, "Log config");
    LOG_INFO(0, "Log info");
    LOG_TRACE(0, "Log trace");
    LOG_DEBUG(0, "Log debug");

    LOG_DEBUG(0, "Integer value: %d", 42);
    LOG_DEBUG(0, "Float value: %f", 31.9);
    LOG_DEBUG(0, "Bool value (true): %d", true);
    LOG_DEBUG(0, "NULL (Using d): %d", NULL);
    LOG_DEBUG(0, "NULL (Using s): %s", NULL);

    LOG_DEBUG(0, "String: %s / Integer: %d / Float: %f / Char: %c", "Hello", 2, 7.1, 'c');

    int counter = 0;
    while(counter < 4) {
        counter++;
        LOG_DEBUG(0, "Log in loop (counter: %d)", counter);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    return 0;
}
