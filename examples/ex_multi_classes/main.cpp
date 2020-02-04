// A simple example with several files using the logger.
// Logger included in several files.

#include <elephantlogger/log.h>

#include "MyClass1.h"
#include "MyClass2.h"

int main(int argc, char** argv) {
    elephantlogger::init();

    LOG_DEBUG("Create MyClass%d", 1);
    MyClass1 myClass1;
    myClass1.foo();

    LOG_DEBUG("Create MyClass%d", 2);
    MyClass2 myClass2;
    myClass2.foo();

    return 0;
}
