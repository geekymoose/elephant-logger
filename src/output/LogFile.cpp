#include "output/LogFile.h"

#include "core/LogMessage.h"

#include <experimental/filesystem>
#include <chrono>


namespace fs = std::experimental::filesystem;
using namespace ElephantLogger;


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------

LogFile::LogFile(std::string filePath, std::string fileName)
  : m_filePath(filePath), m_fileName(fileName) {

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

void LogFile::flush() {
    this->m_stream << std::flush;
}

bool LogFile::save() const {
    using Clock = std::chrono::system_clock;
    std::time_t startTime = Clock::to_time_t(Clock::now());

    char timestamp[20];
    std::strftime(timestamp, 20, "%Y_%m_%d_%H%M%S", std::localtime(&startTime));

    std::lock_guard<std::mutex> lock(m_streamAccess);

    std::string destination = this->m_filePath + "/" + timestamp + "_" + this->m_fileName;
    return this->internal_save(destination);
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

bool LogFile::internal_save(std::string& savePath) const {
    if(this->m_stream.is_open()) {
        auto destination = fs::path(savePath);

        if(fs::exists(destination) && !fs::is_directory(destination)) {
            return false; // Doesn't override existing file.
        }

        fs::copy(this->m_fullPath, destination);
        return true;
    }
    return false;
}
