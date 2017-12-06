#pragma once


#include "../core/Logger.h"


namespace elephantlogger {


/**
 * Properly initialize and cleanup the Logger.
 *
 * \Author  Constantin Masson
 * \since   1.0
 * \date    Nov 2017
 */
class LoggerAutoInstaller {
    public:

        /**
         * Setup and start the whole logger.
         */
        LoggerAutoInstaller() {
            Logger::get().startup();
        }

        /**
         * Shutdown logger.
         */
        ~LoggerAutoInstaller() {
            Logger::get().shutdown();
        }
};


} // End namespace
