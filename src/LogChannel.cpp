#include "LogChannel.h"
#include <fstream>

using namespace ElephantLogger;


LogChannel::LogChannel(std::string const& filePath) {
    this->linkWithFile(filePath);
}

LogChannel::~LogChannel() {
    this->unlinkFile();
}


void LogChannel::writeInFile(std::string const& message) {
    if (this->m_fileOutputStream.is_open()) {
        this->m_fileOutputStream << message << std::endl;
    }
}

bool LogChannel::linkWithFile(std::string const& filePath) {
    if (this->m_fileOutputStream.is_open()) {
        this->m_fileOutputStream.close();
    }
    this->m_pathLogFile = filePath;
    this->m_fileOutputStream.open(filePath, std::ios::out | std::ios::app);

    return this->m_fileOutputStream.is_open();
}

void LogChannel::unlinkFile() {
    if (this->m_fileOutputStream.is_open()) {
        this->m_fileOutputStream.close();
        this->m_pathLogFile.clear();
    }
}