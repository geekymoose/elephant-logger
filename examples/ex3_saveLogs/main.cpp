/*
 * Example to show use of saveLogs function.
 *
 * Author:  Constantin Masson
 * Date:    Nov 2017
 */

#include "elephantlogger/log.h"

#include <chrono>
#include <thread>
#include <signal.h>
#include <string.h>
#include <stdio.h>


// Headers
void sethandler(int sig, void(*f)(int));
void saveAndExit(int x);
void throwException(int x);


// Global vars
bool isRunning = true;


// -----------------------------------------------------------------------------
// Example Main
// -----------------------------------------------------------------------------

int main(int argc, char** argv) {
    elephantlogger::init();

    fprintf(stdout, " ----- Start example 3 - SaveLogs -----\n");
    fprintf(stdout, " - Ctrl+C to stop (Interrupt signal)\n");
    fprintf(stdout, " - Ctrl+\\ to stop (Throw exception)\n");
    fprintf(stdout, " ----- -----\n");

    sethandler(SIGINT, &saveAndExit);
    sethandler(SIGQUIT, &throwException);

    try {
        // The main execution
        int counter = 0;
        while(isRunning) {
            counter++;
            LOG_DEBUG(0, "Log in loop (counter: %d)", counter);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    catch(...) {
        // Save logs because something went wrong.
        LOG_DEBUG(0, "Exception thrown");
    }
    return 0;
}


// -----------------------------------------------------------------------------
// Internal functions
// -----------------------------------------------------------------------------

void throwException(int x) {
    throw 1;
}

void saveAndExit(int x) {
    isRunning = false;
    LOG_DEBUG(0, "Exit requested");
    exit(EXIT_SUCCESS);
}

void sethandler(int sig, void(*f)(int)) {
    struct sigaction sa;
    memset(&sa, 0x0, sizeof(struct sigaction));
    sa.sa_handler = f;
    if(sigaction(sig, &sa, NULL) == -1) {
        perror("sigaction");
        kill(0, SIGTERM);
        exit(EXIT_FAILURE);
    }
}
