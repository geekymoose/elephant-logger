#pragma once

#include <cstdarg>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <sys/time.h>

#include "elephantlogger/details/LogLevel.h"
#include "elephantlogger/details/config.h"

namespace elephantlogger {

// Internal representation of a log message.
class LogMessage
{
  private:
    const LogLevel m_logLevel;
    const int m_categoryID;
    char m_file[config::LOG_FILE_SIZE];
    const int m_line;
    char m_function[config::LOG_FUNCTION_SIZE];
    char m_message[config::LOG_MSG_SIZE];
    const std::time_t m_creationTime;

  public:
    LogMessage(const LogLevel logLevel,
               const int categoryID,
               const char* file,
               const int line,
               const char* function,
               const char* format,
               va_list argList)
      : m_logLevel(logLevel)
      , m_categoryID(categoryID)
      , m_line(line)
      , m_creationTime(std::time(nullptr))
    {
        memcpy(m_file, file, strlen(file));
        memcpy(m_function, function, strlen(function));

        // Message is truncated if length higher than max size.
        vsnprintf(m_message, config::LOG_MSG_SIZE - 1, format, argList); // -1 for '\0'
        m_message[config::LOG_MSG_SIZE - 1] = '\0';
    }

    const std::string getFormattedMessage() const
    {
        std::tm t = *std::localtime(&m_creationTime);
        struct timeval tv;
        gettimeofday(&tv, nullptr);

        std::ostringstream msg;

        msg << "[";
        msg << (t.tm_year + 1900) << "-";                             // Year
        msg << std::setfill('0') << std::setw(2) << t.tm_mon << "-";  // Month
        msg << std::setfill('0') << std::setw(2) << t.tm_mday << " "; // Day
        msg << std::setfill('0') << std::setw(2) << t.tm_hour << ":"; // Hour
        msg << std::setfill('0') << std::setw(2) << t.tm_min << ":";  // Min
        msg << std::setfill('0') << std::setw(2) << t.tm_sec << " ";  // Sec
        msg << tv.tv_usec;                                            // Microseconds

        msg << "] [";

        msg << logLevelToString(m_logLevel);
        msg << "]: ";
        msg << m_message;
        return msg.str();
    }

    LogLevel getLogLevel() const { return this->m_logLevel; }
};

} // End namespace
