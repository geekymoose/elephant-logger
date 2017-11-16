#include "logger/ElephantLogger.h"

#include <chrono>
#include <thread>


// A simple test
int main(int argc, char** argv) {

    ElephantLogger::init();

    LOG_ERROR(0, "1. TEST ERROR");
    LOG_WARNING(0, "2. TEST WARNING");
    LOG_CONFIG(0, "3. TEST CONFIG");
    LOG_INFO(0, "4. TEST INFO");
    LOG_TRACE(0, "5. TEST TRACE");
    LOG_DEBUG(0, "6. TEST DEBUG");

    while(true) {
        LOG_DEBUG(0, "Debug in loop");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    return 0;
}
