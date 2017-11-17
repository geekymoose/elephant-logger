#include "logger/ElephantLogger.h"
#include "MyClass1.h"
#include "MyClass2.h"

#include <thread>

// A simple test with several files using the logger.
int main(int argc, char** argv) {
    ElephantLogger::init();
    LOG_INFO(0, "Start example 2");

    LOG_DEBUG(0, "Create MyClass1");
    MyClass1 myClass1;
    myClass1.foo();

    LOG_DEBUG(0, "Create MyClass2");
    MyClass2 myClass2;
    myClass2.foo();

    LOG_INFO(0, "End exmaple 2");

    /*
    while(true) {
        LOG_DEBUG(0, "Debug in loop");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    */
    return 0;
}
