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

        LogLevel m_currentLogLevel;
        uint64_t m_currentChannelsFilter; // Max nb channels is 64
        std::vector<IOutput *> m_outputs;

    public:

        /**
         * Writes a log for the specified channels.
         *
         * \param level     Log Level for this message.
         * \param channels  The channels related to this log.
         * \param file      File that created the log
         * \param line      Line position in file.
         * \param function  Function's name.
         * \param format    Row message, using printf convention (%s, %d etc).
         * \param argList   Variable list of parameters.
         */
        void log(const LogLevel level,
                 const uint64_t channels,
                 const char * file,
                 const int line,
                 const char * function,
                 const char * format,
                 va_list argList) {
            if(this->passFilter(level, channels)) {
                ELEPHANTLOGGER_ASSERT(channel != 0);

                for(IOutput * output : this->m_outputs) {
                    ELEPHANTLOGGER_ASSERT(output != nullptr);
                    if(output != nullptr && output->passFilter(level, channels)) {
                        LogMessage msg(level, channels, file, line, function, format, argList);
                        output->write(msg);
                    }
                }
            }
        }

        /**
         * Adds an output with the given channels filter (reset old filter if exists).
         * Keep a pointer to this output (beware with variable scope).
         *
         * \param output    The output to add.
         * \param level     Log level for this output.
         * \param channels  Channels filter for this output.
         */
        void addOutput(IOutput * output, const LogLevel level, const uint64_t channels) {
            ELEPHANTLOGGER_ASSERT(output != nullptr);
            ELEPHANTLOGGER_ASSERT(channel != 0);

            if(output != nullptr) {
                output->setLogLevel(level);
                output->setChannelsFilter(channels);
                this->m_outputs.push_back(output);
            }
        }

        bool passFilter(const LogLevel level, const uint64_t channels) const {
            return level <= this->m_currentLogLevel && (channels & this->m_currentChannelsFilter) != 0;
        }

        void setLogLevel(const LogLevel level) {
            this->m_currentLogLevel = level;
        }

        void setChannelsFilter(const uint64_t channels) {
            this->m_currentChannelsFilter = channels;
        }
        void acceptAllChannels() {
            this->m_currentChannelsFilter = UINT64_MAX; // Accept all
        }

    private:

        Logger() {
            this->acceptAllChannels();
            this->m_currentLogLevel = ELEPHANTLOGGER_DEFAULT_LOGLEVEL;
        }

        ~Logger() = default;
};


} // End namespace

