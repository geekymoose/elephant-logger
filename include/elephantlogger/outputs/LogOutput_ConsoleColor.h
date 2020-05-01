#pragma once

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <iostream>
#endif

#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/outputs/LogOutput.h"

namespace elephantlogger {

enum
{
    ELEPHANTLOGGER_XTERM_COLOR_DEFAULT = 0,
    ELEPHANTLOGGER_XTERM_COLOR_ORANGE = 31,
    ELEPHANTLOGGER_XTERM_COLOR_GREEN = 32,
    ELEPHANTLOGGER_XTERM_COLOR_YELLOW = 33,
    ELEPHANTLOGGER_XTERM_COLOR_BLUE = 34,
    ELEPHANTLOGGER_XTERM_COLOR_RED = 35,
};

class LogOutput_ConsoleColor : public LogOutput
{
  public:
    void write(const LogMessage& message) override
    {
#if defined(_WIN32) || defined(_WIN64)
        // TODO not supported
        std::string msg = message.getFormattedMessage() + "\n";
        OutputDebugStringA(static_cast<LPCSTR>(msg.c_str()));
#else
        int color = ELEPHANTLOGGER_XTERM_COLOR_DEFAULT;

        switch (message.getLogLevel()) {
            case LogLevel::Wtf:
                color = ELEPHANTLOGGER_XTERM_COLOR_RED;
                break;
            case LogLevel::Error:
                color = ELEPHANTLOGGER_XTERM_COLOR_RED;
                break;
            case LogLevel::Warning:
                color = ELEPHANTLOGGER_XTERM_COLOR_ORANGE;
                break;
            case LogLevel::Config:
                color = ELEPHANTLOGGER_XTERM_COLOR_YELLOW;
                break;
            case LogLevel::Info:
                color = ELEPHANTLOGGER_XTERM_COLOR_YELLOW;
                break;
            case LogLevel::Trace:
                color = ELEPHANTLOGGER_XTERM_COLOR_BLUE;
                break;
            case LogLevel::Debug:
                color = ELEPHANTLOGGER_XTERM_COLOR_BLUE;
                break;

            default:
                break;
        }

        std::cout << "\e[" << color << "m" << message.getFormattedMessage() << "\e[0m" << std::endl;
#endif
    }
};

} // End namespace
