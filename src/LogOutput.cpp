#include "LogOutput.h"
#include <string>

using namespace ElephantLogger;


LogOutput::LogOutput(std::string const& filePath) {
    this->linkWithFile(filePath);
}

LogOutput::~LogOutput() {
    this->unlinkFile();
}

void LogOutput::writeInFile(std::string const& message) {
    if (this->m_fileOutputStream.is_open()) {
        this->m_fileOutputStream << message << std::endl;
    }
}

bool LogOutput::linkWithFile(std::string const& filePath) {
    if (this->m_fileOutputStream.is_open()) {
        this->m_fileOutputStream.close();
    }

    this->m_pathLogFile = filePath;
    this->m_fileOutputStream.open(filePath, std::ios::out | std::ios::app);

    return this->m_fileOutputStream.is_open();
}

void LogOutput::unlinkFile() {
    if (this->m_fileOutputStream.is_open()) {
        this->m_fileOutputStream.close();
        this->m_pathLogFile.clear();
    }
}
