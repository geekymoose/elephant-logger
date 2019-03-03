/*
 * A simple example with several files using the logger.
 * Shows the use of the logger when included in several files.
 */

#include "elephantlogger/log.h"
#include "MyClass1.h"
#include "MyClass2.h"

#include <thread>

int main(int argc, char** argv) {
    elephantlogger::init();

    LOG_INFO_(0, "Start example 2");

    LOG_DEBUG_(0, "Create MyClass%d", 1);
    MyClass1 myClass1;
    myClass1.foo();

    LOG_DEBUG_(0, "Create MyClass%d", 2);
    MyClass2 myClass2;
    myClass2.foo();

    LOG_INFO_(0, "End exmaple 2");
    return 0;
}
