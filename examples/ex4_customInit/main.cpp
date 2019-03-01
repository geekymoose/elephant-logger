/*
 * Example that uses custom configuration.
 *
 * Author:  Constantin Masson
 * Date:    Nov 2017
 */

#include <elephantlogger/log.h>

// Include Outputs headers
#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/outputs/LogFile.h"

#include <string>


/*
 * Initialize the logger with custom outputs and channels.
 */
static void customInitElephant() {
    static elephantlogger::ConsoleCout  coutConsole;
    static elephantlogger::ConsoleVS    visualConsole;
    static elephantlogger::LogFile      coutFile("elephant_cout.log");
    static elephantlogger::LogFile      visualFile("elephant_vs.log");
    static elephantlogger::LogFile      generalFile("elephant.log");

    elephantlogger::init();

    elephantlogger::addOutput(0, &coutConsole);
    elephantlogger::addOutput(0, &coutFile);
    elephantlogger::addOutput(1, &visualConsole);
    elephantlogger::addOutput(1, &visualFile);

    // All logs fowarded in generalFile
    elephantlogger::addOutput(0, &generalFile);
    elephantlogger::addOutput(1, &generalFile);
    elephantlogger::addOutput(2, &generalFile);
}

void foo() {
    LOG_WARNING(0, "Some warning log");
    LOG_DEBUG(0, "Some debug log");
    LOG_ERROR(0, "Some error log");
    LOG_CONFIG(0, "Some config log");
    LOG_TRACE(0, "Some trace log");
    LOG_INFO(0, "Some information log");
}

int main(int argc, char** argv) {
    customInitElephant();


    LOG_CONFIG(0, "Start example 4");

    foo(); // Your code

    LOG_CONFIG(0, "Stop example 4");
    return 0;
}
