#pragma once

#include <cstdarg>
#include <vector>

#include "elephantlogger/details/LogFilter.h"
#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/LogMessage.h"
#include "elephantlogger/details/config.h"
#include "elephantlogger/details/utils.h"
#include "elephantlogger/outputs/LogOutput.h"

namespace elephantlogger {

/**
 * Nellie, the famous elephant logger.
 * She's thirsty of logs and will remember all of them!
 */
class Logger : private Singleton<Logger>
{
    ELEPHANTLOGGER_ADD_SINGLETON_UTILS(Logger);

  private:
    bool m_isEnabled;
    LogFilter m_filter;
    std::vector<LogOutput*> m_outputs;

  public:
    void log(const LogLevel level,
             const uint64_t categories,
             const char* file,
             const int line,
             const char* function,
             const char* format,
             va_list argList)
    {
        ELEPHANTLOGGER_ASSERT(categories != 0);

        for (LogOutput* output : this->m_outputs) {
            ELEPHANTLOGGER_ASSERT(output != nullptr);
            if (output != nullptr && output->isEnabled() && output->filter().passFilters(level, categories)) {
                LogMessage msg(level, categories, file, line, function, format, argList);
                output->write(msg);
            }
        }
    }

    void addOutput(LogOutput* output, const LogLevel level)
    {
        ELEPHANTLOGGER_ASSERT(output != nullptr);
        ELEPHANTLOGGER_ASSERT(categories != 0);

        if (output != nullptr) {
            output->filter().setLogLevel(level);
            this->m_outputs.push_back(output);
        }
    }

    void enable() { this->m_isEnabled = true; }

    void disable() { this->m_isEnabled = false; }

    bool isEnabled() const { return this->m_isEnabled; }

    LogFilter& filter() { return this->m_filter; }

    LogFilter const& filter() const { return this->m_filter; }

  private:
    Logger() { this->m_isEnabled = true; }
};

} // End namespace
