#include "core/LogMessage.h"

#include <string>


using namespace ElephantLogger;


LogMessage::LogMessage(const LogLevel logLevel,
                       const int channelID,
                       std::string&& message,
                       std::string&& file,
                       const int line)
    : m_logLevel(logLevel),
      m_channelID(channelID),
      m_message(std::move(message)),
      m_filePosition(std::move(file)),
      m_linePosition(line),
      m_creationTime(std::time(nullptr)) {
}

const std::string LogMessage::getFormattedMessage() const {
    std::string dateStr = ctime(&this->m_creationTime);
    dateStr.pop_back(); // Remove line return

    std::string msg = "[" + dateStr +"] ";
    msg += "[";
    msg += LogLevelHelper::logLevelToString(this->m_logLevel);
    msg += "]: ";
    msg += this->m_message;
    return msg;
}

const int LogMessage::getChannelID() const {
    return this->m_channelID;
}

