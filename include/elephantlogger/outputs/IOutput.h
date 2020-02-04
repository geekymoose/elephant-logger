#pragma once

#include <stdint.h>
#include "elephantlogger/details/config.h"
#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/LogMessage.h"


namespace elephantlogger {

class IOutput {
    private:
        LogLevel m_currentLogLevel;
        uint64_t m_currentCategoriesFilter;

    public:
        virtual ~IOutput() = default;

        virtual void write(const LogMessage & message) = 0;

        bool passFilters(const LogLevel level, const uint64_t categories) const {
            return level <= this->m_currentLogLevel && (categories & this->m_currentCategoriesFilter) != 0;
        }

        void setLogLevel(const LogLevel level) {
            this->m_currentLogLevel = level;
        }

        void setCategoriesFilter(const uint64_t categories) {
            this->m_currentCategoriesFilter = categories;
        }

        void enableAllCategories() {
            this->m_currentCategoriesFilter = UINT64_MAX; // Accept all
        }

        void enableCategories(const uint64_t categories) {
            this->m_currentCategoriesFilter |= categories;
        }

        void disableCategories(const uint64_t categories) {
            this->m_currentCategoriesFilter ^= categories;
        }

    protected:
        IOutput() {
            this->m_currentLogLevel = ELEPHANTLOGGER_DEFAULT_LOGLEVEL;
            this->enableAllCategories(); // Accept all by default
        }
};


}

