#pragma once

#include <mutex>
#include <stdint.h>

#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/config.h"

namespace elephantlogger {

class LogFilter
{
  private:
    LogLevel m_currentLogLevel;
    uint64_t m_currentCategoriesFilter;
    std::mutex m_mutex;

  public:
    bool passFilters(const LogLevel level, const uint64_t categories) const
    {
        return level <= this->m_currentLogLevel && (categories & this->m_currentCategoriesFilter) != 0;
    }

    void setLogLevel(const LogLevel level)
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_currentLogLevel = level;
    }

    void setCategoriesFilter(const uint64_t categories)
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_currentCategoriesFilter = categories;
    }

    void enableCategories(const uint64_t categories)
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_currentCategoriesFilter |= categories;
    }

    void disableCategories(const uint64_t categories)
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_currentCategoriesFilter ^= categories;
    }

    void enableAllCategories()
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_currentCategoriesFilter = UINT64_MAX; // Accept all
    }

    void disableAllCategories()
    {
        std::lock_guard<std::mutex> lk(this->m_mutex);
        this->m_currentCategoriesFilter = 0;
    }

    LogFilter()
    {
        this->m_currentLogLevel = ELEPHANTLOGGER_DEFAULT_LOGLEVEL;
        this->enableAllCategories(); // Accept all by default
    }
};

} // End namespace
