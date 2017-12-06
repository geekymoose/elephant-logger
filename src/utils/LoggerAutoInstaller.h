#pragma once


#include "../core/Logger.h"


namespace elephantlogger {


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
