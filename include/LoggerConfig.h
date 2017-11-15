#pragma once

#include "core/LogLevel.h"

#include <string>
#include <experimental/filesystem>


namespace fs = std::experimental::filesystem;
namespace ElephantLogger {


/**
 * All configuration for this Logger.
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

    public:
        static const int maxNbChannels = 10;
        int nbChannels;


    public:
        void setDefaultConfig() {
            this->threadUpdateRate      = 250;
            this->logLevel              = LogLevel::Debug;
            this->logFilePath           = fs::temp_directory_path().c_str();
            this->clearAtStart          = true;
            this->nbChannels            = 3;
        }
};


} // End namespace
