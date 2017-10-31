#pragma once

#include <experimental\filesystem>


#define LOGGER_SETTINGS_DEFAULT_LOGPATH std::experimental::filesystem::temp_directory_path().string() + "/MoonRPGLog/"
#define LOGGER_SETTINGS_DEFAULT_LOGPATH_SAVE std::experimental::filesystem::temp_directory_path().string() + "/MoonRPGLog_SAVE/"

#define LOGGER_SETTINGS_DEFAULT_LOG_IN_FILE true
#define LOGGER_SETTINGS_DEFAULT_ERASE_FILE_AT_START true

#define LOGGER_SETTINGS_DEFAULT_LOG_LEVEL MoonRPG::LogLevel::Debug


namespace MoonRPG {

    enum {
        LOGGER_THREAD_UPDATE_RATE_IN_MILLISECONDS = 250
    };

} // End MoonRPG namespace