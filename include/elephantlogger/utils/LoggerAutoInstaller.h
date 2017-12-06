#pragma once


#include "elephantlogger/logger/Logger.h"


namespace elephant {


/**
 * Properly initialize and cleanup the Logger.
 *
 * \Author  Constantin Masson
 * \date    Nov 2017
 */
class LoggerAutoInstaller {
    public:
        LoggerAutoInstaller() {
            Logger::get().startup();
        }

        ~LoggerAutoInstaller() {
            Logger::get().shutdown();
        }
};


} // End namespace
