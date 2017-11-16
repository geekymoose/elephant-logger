#include "Logger.h"

#include "LoggerConfig.h"
#include "LogOutputCout.h"
#include "LogOutputVS.h"

#include <ctime>
#include <experimental/filesystem>

using namespace ElephantLogger;


// -----------------------------------------------------------------------------
// Init
// -----------------------------------------------------------------------------

void Logger::startup() {
    if (this->m_isRunning) {
        return;
    }

    this->m_isRunning           = true;
    this->m_queueLogsFront      = &m_queueLogs1;
    this->m_queueLogsBack       = &m_queueLogs2;
    this->m_isLogingInFile      = LOGGER_SETTINGS_DEFAULT_LOG_IN_FILE;
    this->m_logFilePath         = LOGGER_SETTINGS_DEFAULT_LOGPATH;
    this->m_logFileSavePath     = LOGGER_SETTINGS_DEFAULT_LOGPATH_SAVE;
    this->setLogLevel(LOGGER_SETTINGS_DEFAULT_LOG_LEVEL);

    // Register all available log channles. (To add a new, place it here)
    this->m_lookupChannels[static_cast<size_t>(LogOutputType::Vs)]   = std::unique_ptr<LogOutputVS>(new LogOutputVS());
    this->m_lookupChannels[static_cast<size_t>(LogOutputType::Cout)] = std::unique_ptr<LogOutputCout>(new LogOutputCout());

    if (this->m_isLogingInFile) {
        // Warning: Erase before linkWithFile() otherwise, files stream are opened.
        if (LOGGER_SETTINGS_DEFAULT_ERASE_FILE_AT_START) {
            if (std::experimental::filesystem::exists(this->m_logFilePath)) {
                std::experimental::filesystem::remove_all(m_logFilePath);
            }
        }

        std::experimental::filesystem::create_directory(this->m_logFilePath);
        std::experimental::filesystem::create_directory(this->m_logFileSavePath);

        std::string vsLogPath   = this->m_logFilePath + "/vs.log";
        std::string coutLogPath = this->m_logFilePath + "/cout.log";

        this->m_lookupChannels[static_cast<size_t>(LogOutputType::Vs)]->linkWithFile(vsLogPath);
        this->m_lookupChannels[static_cast<size_t>(LogOutputType::Cout)]->linkWithFile(coutLogPath);
    }

    this->internalStartLoggerThread();
}

void Logger::shutdown() {
    this->m_isRunning = false;
    this->internalProcessBackQueue();
    this->internalSwapQueues();
    this->internalProcessBackQueue();
    this->m_isLogingInFile = false;
}


// -----------------------------------------------------------------------------
// Core Methods
// -----------------------------------------------------------------------------

void Logger::queueLog(LogLevel level,
                             LogOutputType output,
                             char const* message,
                             char const* file,
                             int line) {
    if (this->m_isRunning && this->getLogLevel() >= level) {
        this->internalQueueLog(level, output, message, file, line);
    }
}

bool Logger::saveAllLogFiles() const {
    if (this->m_isLogingInFile) {
        using Clock = std::chrono::system_clock;
        std::time_t startTime = Clock::to_time_t(Clock::now());
        char timestamp[30];
        // TODO: Saved log name may be exported in config.
        std::strftime(timestamp, 30, "/%Y_%m_%d_%H%M%S_SavedLogs/", std::localtime(&startTime));

        try {
            auto saveFolder = std::experimental::filesystem::path(this->m_logFileSavePath + timestamp);
            bool res = std::experimental::filesystem::create_directory(saveFolder);
            if (res == true) {
                std::experimental::filesystem::copy(this->m_logFilePath, saveFolder);
            }
            return res;
        }
        catch (const std::experimental::filesystem::filesystem_error& e) {
            return false;
        }
    }
    return false;
}


// -----------------------------------------------------------------------------
// Internal Methods
// -----------------------------------------------------------------------------

void Logger::internalQueueLog(LogLevel level,
                                     LogOutputType output,
                                     std::string message,
                                     std::string file,
                                     const int line) {
    // Message passed by copie, otherwise, local scope of variable would destroye it.
    std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);
    this->m_queueLogsFront->emplace_back(level, output, std::move(message), std::move(file), line);
}

void Logger::internalProcessBackQueue() {
    for (LogMessage& msg : *this->m_queueLogsBack) {
        std::string formattedMessage = msg.getFormattedMessage();

        auto& coco = m_lookupChannels[static_cast<size_t>(msg.getLogOutput())];
        coco->print(formattedMessage);

        if (this->m_isLogingInFile) {
            coco->writeInFile(formattedMessage);
        }
    }

    this->m_queueLogsBack->clear();
}

void Logger::internalSwapQueues() {
    std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);
    std::swap(this->m_queueLogsFront, this->m_queueLogsBack);
}

void Logger::internalStartLoggerThread() {
    std::thread {
        [this]() {
        while (this->m_isRunning) {
            std::this_thread::sleep_for(std::chrono::milliseconds{
                ElephantLogger::LOGGER_THREAD_UPDATE_RATE_IN_MILLISECONDS}
            );
            this->internalProcessBackQueue();
            this->internalSwapQueues();
        }
    }
    }.detach();
}


// -----------------------------------------------------------------------------
// Getter - Setters
// -----------------------------------------------------------------------------

void Logger::setLogLevel(const LogLevel level) {
    this->m_currentLogLevel = static_cast<int8_t>(level);
}

LogLevel Logger::getLogLevel() const {
    return static_cast<LogLevel>(this->m_currentLogLevel.load());
}

void Logger::disableLogInFile() {
    this->m_isLogingInFile = false;
}

void Logger::enableLogInFile() {
    this->m_isLogingInFile = true;
}
