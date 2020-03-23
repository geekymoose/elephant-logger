// A simple example with the default configuration

#include <elephantlogger/log.h>

int main(int argc, char** argv)
{
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
    while (counter < 12) {
        counter++;
        LOG_DEBUG("Log in loop (counter: %d)", counter);
    }

    return 0;
}
