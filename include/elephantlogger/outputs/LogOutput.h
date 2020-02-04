#pragma once

#include <stdint.h>
#include "elephantlogger/details/config.h"
#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/LogFilter.h"
#include "elephantlogger/details/LogMessage.h"


namespace elephantlogger {

class LogOutput {

    private:

        LogFilter m_filter;

    public:

        virtual ~LogOutput() = default;
        virtual void write(const LogMessage & message) = 0;

        LogFilter & filter() { return this->m_filter; }
        LogFilter const& filter() const { return this->m_filter; }
};


}

