#include "ElephantLogger.h"

#include <chrono>
#include <thread>

// A simple test
int main(int argc, char** argv) {

    ElephantLogger::LoggerManager::getInstance().startup();

    LOG_ERROR("1. TEST ERROR");
    LOG_WARNING("2. TEST WARNING");
    LOG_CONFIG("3. TEST CONFIG");
    LOG_INFO("4. TEST INFO");
    LOG_TRACE("5. TEST TRACE");
    LOG_DEBUG("6. TEST DEBUG");

    while(true) {
        LOG_DEBUG("Debug in loop");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
