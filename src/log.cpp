#include "elephantlogger/log.h"
#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/outputs/LogFile.h"

#include "utils/config.h"
#include "core/Logger.h"
#include "utils/LoggerAutoInstaller.h"

#include <stdarg.h> // va_args


namespace elephantlogger {


void init() {
    // Use of autoinstaller to properly cleanup logger thread before destroyed.
    static LoggerAutoInstaller elephantLoggerEngine;
}

void initDefault() {
    static ConsoleCout  coutConsole;
    static ConsoleVS    visualConsole;
    static LogFile      coutFile(getTmpFilePath(),    "elephant-cout.log");
    static LogFile      visualFile(getTmpFilePath(),  "elephant-vs.log");
    static LogFile      generalFile(getTmpFilePath(), "elephant.log");

    init();

    Logger::get().addOutput(0, &coutConsole);
    Logger::get().addOutput(0, &coutFile);
    Logger::get().addOutput(1, &visualConsole);
    Logger::get().addOutput(1, &visualFile);
    Logger::get().addOutput(2, &generalFile);
}

void saveLogs(const char* path) {
    Logger::get().saveAllLogs(path);
}

void addOutput(const int channelID, IOutput* output) {
    Logger::get().addOutput(channelID, output);
}

void setLogLevel(const LogLevel level) {
    Logger::get().setLogLevel(level);
}

const char* getTmpFilePath() {
    return ELEPHANT_CONFIG_TMP_PATH;
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


} // End namespace
