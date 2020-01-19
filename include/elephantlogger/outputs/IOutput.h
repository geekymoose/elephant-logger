#pragma once

#include <stdint.h>
#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/LogMessage.h"


namespace elephantlogger {

class IOutput {
    private:
        LogLevel m_currentLogLevel;
        uint64_t m_currentChannelsFilter;

    public:
        virtual ~IOutput() = default;

        virtual void write(const LogMessage & message) = 0;

        bool passFilters(const LogLevel level, const uint64_t channels) const {
            return level <= this->m_currentLogLevel && (channels & this->m_currentChannelsFilter) != 0;
        }

        void setChannelsFilter(const uint64_t channels) {
            this->m_currentChannelsFilter = channels;
        }

        void setLogLevel(const LogLevel level) {
            this->m_currentLogLevel = level;
        }

    protected:
        IOutput() {
            this->m_currentLogLevel = LogLevel::Debug;
            this->m_currentChannelsFilter = UINT64_MAX; // Accept all by default
        }
};


}

