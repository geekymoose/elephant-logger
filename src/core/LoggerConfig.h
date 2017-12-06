#pragma once

#include "Channel.h"
#include "elephantlogger/core/LogLevel.h"
#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/outputs/LogFile.h"

#include <string>
#include <memory> // unique_ptr
#include <experimental/filesystem> // For tmp path


namespace fs = std::experimental::filesystem;
namespace elephantlogger {


/**
 * All configuration for this Logger.
 *
 * \note
 * TODO
 * Only hard coded configuration is implemented.
 * Update would be to use JSON configuration file to fill up this data.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Nov, 2017
 */
class LoggerConfig {
    public:
        LogLevel        logLevel;
        std::string     logFilePath;
        bool            clearAtStart;
        int             threadUpdateRate;
        int             defaultQueueSize;

    public:
        static const int maxNbChannels = 10;
        int nbChannels;


    public:
        /**
         * Reset this config class to all its default value.
         * This doesn't affect the logger, only this config file.
         * (Use the applyConfig method in Logger to apply this config).
         */
        void setDefaultConfig() {
            this->threadUpdateRate      = 250;
            this->logLevel              = LogLevel::Debug;
            this->clearAtStart          = true;
            this->nbChannels            = 3;
            this->defaultQueueSize      = 30;
            this->logFilePath           = fs::temp_directory_path().c_str();
            this->logFilePath           += "/ElephantLogs/";
        }
};


} // End namespace


