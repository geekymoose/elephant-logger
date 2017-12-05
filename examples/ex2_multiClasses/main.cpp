#include "elephantlogger.h"
#include "MyClass1.h"
#include "MyClass2.h"

#include <thread>

// A simple example with several files using the logger.
int main(int argc, char** argv) {
    elephant::init();
    LOG_INFO(0, "Start example 2");

    LOG_DEBUG(0, "Create MyClass%d", 1);
    MyClass1 myClass1;
    myClass1.foo();

    LOG_DEBUG(0, "Create MyClass%d", 2);
    MyClass2 myClass2;
    myClass2.foo();

    LOG_INFO(0, "End exmaple 2");
    return 0;
}
