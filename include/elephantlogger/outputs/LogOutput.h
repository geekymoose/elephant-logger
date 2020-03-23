#pragma once

#include "elephantlogger/details/LogFilter.h"
#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/LogMessage.h"
#include "elephantlogger/details/config.h"

#include <stdint.h>

namespace elephantlogger {

class LogOutput
{
  private:
    bool m_isEnabled = true;
    LogFilter m_filter;

  public:
    virtual ~LogOutput() = default;
    virtual void write(const LogMessage& message) = 0;

    void enable() { this->m_isEnabled = true; }

    void disable() { this->m_isEnabled = false; }

    bool isEnabled() const { return this->m_isEnabled; }

    LogFilter& filter() { return this->m_filter; }

    LogFilter const& filter() const { return this->m_filter; }
};

}
