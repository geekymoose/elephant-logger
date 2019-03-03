#include "elephantlogger/log.h"

#include "elephantlogger/outputs/ConsoleOutput.h"

#include "core/Logger.h"


namespace elephantlogger {


void init(const LogLevel level) {
    static ConsoleOutput console;
    Logger::get().addOutput(0, &console);
    Logger::get().setLogLevel(level);
    Logger::get().startup();
}

void addOutput(const int channelID, IOutput * output) {
    Logger::get().addOutput(channelID, output);
}

void setLogLevel(const LogLevel level) {
    Logger::get().setLogLevel(level);
}

void log(const LogLevel level,
         const int channelID,
         const char * file,
         const int line,
         const char * function,
         const char * format,
         ...) {
    if(Logger::get().isLogLevelAccepted(level)) {
        va_list argList;
        va_start(argList, format);
        Logger::get().queueLog(level, channelID, file, line, function, format, argList);
        va_end(argList);
    }
}


} // End namespace

