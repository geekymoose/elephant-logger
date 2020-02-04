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
        uint64_t m_currentCategoriesFilter; // Max nb categories is 64
        std::vector<IOutput *> m_outputs;

    public:

        void log(const LogLevel level,
                 const uint64_t categories,
                 const char * file,
                 const int line,
                 const char * function,
                 const char * format,
                 va_list argList) {
            if(this->m_enabled && this->passFilters(level, categories)) {
                ELEPHANTLOGGER_ASSERT(category != 0);

                for(IOutput * output : this->m_outputs) {
                    ELEPHANTLOGGER_ASSERT(output != nullptr);
                    if(output != nullptr && output->passFilters(level, categories)) {
                        LogMessage msg(level, categories, file, line, function, format, argList);
                        output->write(msg);
                    }
                }
            }
        }

        void addOutput(IOutput * output, const LogLevel level, const uint64_t categories) {
            ELEPHANTLOGGER_ASSERT(output != nullptr);
            ELEPHANTLOGGER_ASSERT(category != 0);

            if(output != nullptr) {
                output->setLogLevel(level);
                output->setCategoriesFilter(categories);
                this->m_outputs.push_back(output);
            }
        }

        bool passFilters(const LogLevel level, const uint64_t categories) const {
            return level <= this->m_currentLogLevel && (categories & this->m_currentCategoriesFilter) != 0;
        }

        void setLogLevel(const LogLevel level) {
            this->m_currentLogLevel = level;
        }

        void setEnabled(const bool enabled) {
            this->m_enabled = enabled;
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

    private:

        Logger() {
            this->m_enabled = true;
            this->m_currentLogLevel = ELEPHANTLOGGER_DEFAULT_LOGLEVEL;
            this->enableAllCategories();
        }
};


} // End namespace

