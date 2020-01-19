#pragma once

#include <vector>
#include <cstdarg>
#include <cmath>
#include <stdint.h>

#include "elephantlogger/outputs/IOutput.h"
#include "LogLevel.h"
#include "LogMessage.h"
#include "config.h"
#include "utils.h"


namespace elephantlogger {

/**
 * Nellie, the famous elephant logger.
 * She's thirsty of logs and will remember all of them!
 */
class Logger : private Singleton<Logger> {
    ELEPHANTLOGGER_ADD_SINGLETON_UTILS(Logger);

    private:

        bool m_enabled;
        LogLevel m_currentLogLevel;
        uint64_t m_currentChannelsFilter; // Max nb channels is 64
        std::vector<IOutput *> m_outputs;

    public:

        void log(const LogLevel level,
                 const uint64_t channels,
                 const char * file,
                 const int line,
                 const char * function,
                 const char * format,
                 va_list argList) {
            if(this->m_enabled && this->passFilters(level, channels)) {
                ELEPHANTLOGGER_ASSERT(channel != 0);

                for(IOutput * output : this->m_outputs) {
                    ELEPHANTLOGGER_ASSERT(output != nullptr);
                    if(output != nullptr && output->passFilters(level, channels)) {
                        LogMessage msg(level, channels, file, line, function, format, argList);
                        output->write(msg);
                    }
                }
            }
        }

        void addOutput(IOutput * output, const LogLevel level, const uint64_t channels) {
            ELEPHANTLOGGER_ASSERT(output != nullptr);
            ELEPHANTLOGGER_ASSERT(channel != 0);

            if(output != nullptr) {
                output->setLogLevel(level);
                output->setChannelsFilter(channels);
                this->m_outputs.push_back(output);
            }
        }

        bool passFilters(const LogLevel level, const uint64_t channels) const {
            return level <= this->m_currentLogLevel && (channels & this->m_currentChannelsFilter) != 0;
        }

        void setLogLevel(const LogLevel level) {
            this->m_currentLogLevel = level;
        }

        void setEnabled(const bool enabled) {
            this->m_enabled = enabled;
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

    private:

        Logger() {
            this->m_enabled = true;
            this->enableAllChannels();
            this->m_currentLogLevel = ELEPHANTLOGGER_DEFAULT_LOGLEVEL;
        }
};


} // End namespace

