#include "elephantlogger/outputs/LogFile.h"
#include "elephantlogger/core/LogMessage.h"

#include <experimental/filesystem>
#include <chrono>


namespace fs = std::experimental::filesystem;
using namespace elephantlogger;


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

LogFile::LogFile(const std::string filePath, const std::string fileName)
    : m_filePath(filePath),
      m_fileName(fileName) {

    fs::create_directory(this->m_filePath);
    this->m_fullPath = this->m_filePath + this->m_fileName;
    this->m_stream.open(this->m_fullPath);
}

LogFile::~LogFile() {
    if(this->m_stream.is_open()) {
        this->m_stream.close();
    }
}


// -----------------------------------------------------------------------------
// Core public methods
// -----------------------------------------------------------------------------

void LogFile::write(const LogMessage & message) {
    std::lock_guard<std::mutex> lock(m_streamAccess);

    if(this->m_stream.is_open()) {
        this->m_stream << message.getFormattedMessage() << std::endl;
    }
}

bool LogFile::save(const char* path) const {
    std::lock_guard<std::mutex> lock(m_streamAccess);

    if(this->m_stream.is_open()) {
        using Clock = std::chrono::system_clock;
        std::time_t startTime = Clock::to_time_t(Clock::now());

        char timestamp[20];
        std::strftime(timestamp, 20, "%Y_%m_%d_%H%M%S", std::localtime(&startTime));

        return this->internal_save(path, timestamp);
    }
    return false;
}

void LogFile::flush() {
    if(this->m_stream.is_open()) {
        std::lock_guard<std::mutex> lock(m_streamAccess);
        this->m_stream << std::flush;
    }
}

void LogFile::clear() {
    std::lock_guard<std::mutex> lock(m_streamAccess);

    if(this->m_stream.is_open()) {
        this->m_stream.close();
        this->m_stream.open(this->m_fullPath, std::ofstream::trunc);
    }
}


// -----------------------------------------------------------------------------
// Internal
// -----------------------------------------------------------------------------

bool LogFile::internal_save(const char* path, const char* timestamp) const {

    std::string fullSavePath = std::string(path) + "/" + timestamp + "_" + this->m_fileName;

    auto saveDir            = fs::path(path);
    auto saveDestination    = fs::path(fullSavePath);

    if(fs::exists(saveDestination) && !fs::is_directory(saveDestination)) {
        return false; // Doesn't override existing file.
    }

    try{
        fs::create_directory(saveDir);
        fs::copy(this->m_fullPath, saveDestination);
    }
    catch(const fs::filesystem_error& e) {
        return false;
    }
    return true;
}
