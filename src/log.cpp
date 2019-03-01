#include "elephantlogger/log.h"
#include "elephantlogger/core/config.h"
#include "elephantlogger/outputs/ConsoleCout.h"
#include "elephantlogger/outputs/ConsoleVS.h"
#include "elephantlogger/outputs/LogFile.h"

#include "core/Logger.h"


namespace elephantlogger {


void init() {
    Logger::get().startup();
}

void initDefault() {
    static ConsoleVS    visualConsole;
    static LogFile      coutFile("elephant_cout.log");
    static LogFile      visualFile("elephant_vs.log");
    static LogFile      generalFile("elephant_normal.log");

    init();

    Logger::get().addOutput(0, &coutFile);
    Logger::get().addOutput(1, &visualConsole);
    Logger::get().addOutput(1, &visualFile);
    Logger::get().addOutput(2, &generalFile);
}

void addOutput(const int channelID, IOutput* output) {
    Logger::get().addOutput(channelID, output);
}

void setLogLevel(const LogLevel level) {
    Logger::get().setLogLevel(level);
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

