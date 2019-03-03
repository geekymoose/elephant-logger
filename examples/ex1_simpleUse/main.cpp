// A simple example with default configuration

#include "elephantlogger/log.h"

#include <chrono>
#include <thread>


int main(int argc, char** argv) {

    elephantlogger::init();

    LOG_WTF("Log WTF");
    LOG_ERROR("Log error");
    LOG_WARNING("Log warning");
    LOG_CONFIG("Log config");
    LOG_INFO("Log info");
    LOG_TRACE("Log trace");
    LOG_DEBUG("Log debug");

    LOG_DEBUG("Integer value: %d", 42);
    LOG_DEBUG("Float value: %f", 31.9);
    LOG_DEBUG("Bool value (true): %d", true);
    LOG_DEBUG("NULL (Using d): %d", NULL);
    LOG_DEBUG("NULL (Using s): %s", NULL);

    LOG_DEBUG("String: %s / Integer: %d / Float: %f / Char: %c", "Hello", 2, 7.1, 'c');

    int counter = 0;
    while(counter < 4) {
        counter++;
        LOG_DEBUG("Log in loop (counter: %d)", counter);
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    return 0;
}
