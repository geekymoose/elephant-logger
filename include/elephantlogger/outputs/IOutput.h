#pragma once

#include <stdint.h>
#include "elephantlogger/details/config.h"
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

        void setLogLevel(const LogLevel level) {
            this->m_currentLogLevel = level;
        }

        void setChannelsFilter(const uint64_t channels) {
            this->m_currentChannelsFilter = channels;
        }

        void enableAllChannels() {
            this->m_currentChannelsFilter = UINT64_MAX; // Accept all
        }

        void enableChannels(const uint64_t channels) {
            this->m_currentChannelsFilter |= channels;
        }

        void disableChannels(const uint64_t channels) {
            this->m_currentChannelsFilter ^= channels;
        }

    protected:
        IOutput() {
            this->m_currentLogLevel = ELEPHANTLOGGER_DEFAULT_LOGLEVEL;
            this->enableAllChannels(); // Accept all by default
        }
};


}

