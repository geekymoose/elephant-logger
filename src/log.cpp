#include "elephantlogger/log.h"
#include "elephantlogger/core/config.h"
#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/outputs/LogFile.h"

#include "core/Logger.h"

#include <experimental/filesystem> // For tmp path


namespace elephantlogger {


void init() {
    // Use of autoinstaller to properly cleanup logger thread before destroyed.
    Logger::get().startup();
}

void initDefault() {
    const std::string logPath = getTmpFilePath() + "/elephant_logs/";
    static ConsoleCout  coutConsole;
    static ConsoleVS    visualConsole;
    static LogFile      coutFile(logPath,    "elephant-cout.log");
    static LogFile      visualFile(logPath,  "elephant-vs.log");
    static LogFile      generalFile(logPath, "elephant.log");

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

std::string getTmpFilePath() {
    namespace fs = std::experimental::filesystem;
    fs::path dir = fs::temp_directory_path();
    return dir;
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
