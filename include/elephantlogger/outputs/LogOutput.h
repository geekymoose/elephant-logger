#pragma once

#include <mutex>

#include "elephantlogger/details/LogFilter.h"
#include "elephantlogger/details/LogMessage.h"

namespace elephantlogger {

class LogOutput
{
  private:
    bool m_isEnabled = true;
    LogFilter m_filter;
    std::mutex m_mutex;

  public:
    virtual ~LogOutput() = default;
    virtual void write(const LogMessage& message) = 0;

    void enable()
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_isEnabled = true;
    }

    void disable()
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_isEnabled = false;
    }

    bool isEnabled() const { return this->m_isEnabled; }

    LogFilter& filter() { return this->m_filter; }

    LogFilter const& filter() const { return this->m_filter; }
};

} // End namespace
