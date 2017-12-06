#include "elephantlogger/log.h"
#include "core/Logger.h"
#include "utils/LoggerAutoInstaller.h"
#include <stdarg.h> // va_args


namespace elephantlogger {

    void init() {
        // Use of autoinstaller to properly cleanup logger thread before destroyed.
        static LoggerAutoInstaller elephantLoggerEngine;
    }

    void saveLogs() {
        Logger::get().saveAllLogs();
    }

    void log(const LogLevel level,
             const int channelID,
             const char* file,
             const int line,
             const char* function,
             const char* format,
             ...) {
        if(Logger::get().isAcceptedLogLevel(level)) {
            va_list argList;
            va_start(argList, format);
            Logger::get().queueLog(level, channelID, file, line, function, format, argList);
            va_end(argList);
        }
    }

    void setLogLevel(const LogLevel level) {
        Logger::get().setLogLevel(level);
    }
}
