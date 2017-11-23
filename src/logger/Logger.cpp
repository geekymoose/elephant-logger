#include "logger/Logger.h"


using namespace elephant;


// -----------------------------------------------------------------------------
// Init
// -----------------------------------------------------------------------------

Logger::~Logger() {
    this->shutdown();
}

void Logger::startup() {
    if (this->m_isRunning) {
        return;
    }

    this->m_isRunning           = true;
    this->m_queueLogsFront      = &m_queueLogs1;
    this->m_queueLogsBack       = &m_queueLogs2;

    LoggerConfig conf;
    conf.setDefaultConfig();
    this->applyConfig(conf);
    conf.applyDefaultOutputs(this->m_lookupChannels);

    if(this->clearAtStart) {
        for(int k = 0; k < this->nbChannels; ++k) {
            this->m_lookupChannels[k]->clear();
        }
    }

    this->internalStartLoggerThread();
}

void Logger::shutdown() {
    this->m_isRunning = false;
    this->internalProcessBackQueue();
    this->internalSwapQueues();
    this->internalProcessBackQueue();
}


// -----------------------------------------------------------------------------
// Core Methods
// -----------------------------------------------------------------------------

void Logger::queueLog(LogLevel level,
                      const int channelID,
                      const char* file,
                      const int line,
                      const char* function,
                      const char* format,
                      ...) {
    if (this->m_isRunning && this->getLogLevel() >= level) {
        va_list argList;
        va_start(argList, format);
        this->internalQueueLog(level, channelID, file, line, function, format, argList);
        va_end(argList);
    }
}

bool Logger::saveAllLogFiles() const {
    for(int k = 0; k < this->nbChannels; ++k) {
        this->m_lookupChannels[k]->save();
    }
    return false;
}


// -----------------------------------------------------------------------------
// Internal Methods
// -----------------------------------------------------------------------------

void Logger::internalQueueLog(LogLevel level,
                              const int channelID,
                              const char* file,
                              const int line,
                              const char* function,
                              const char* format,
                              va_list argList) {
    std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);
    this->m_queueLogsFront->emplace_back(level, channelID, file, line, function, format, argList);
}

void Logger::internalProcessBackQueue() {
    for (LogMessage& msg : *this->m_queueLogsBack) {
        int index = msg.getChannelID();
        if(index < this->nbChannels) {
            auto& coco = m_lookupChannels[static_cast<size_t>(index)];
            coco->write(msg);
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
                    this->threadUpdateRate
                });
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

void Logger::applyConfig(const LoggerConfig& config) {
    this->setLogLevel(config.logLevel);
    this->nbChannels        = config.nbChannels;
    this->m_logFilePath     = config.logFilePath;
    this->threadUpdateRate  = config.threadUpdateRate;
    this->clearAtStart      = config.clearAtStart;
    this->defaultQueueSize  = config.defaultQueueSize;

    for(int k = 0; k < this->nbChannels; ++k) {
        this->m_lookupChannels[k] = std::unique_ptr<Channel>(new Channel());
    }

    this->m_queueLogs1.reserve(this->defaultQueueSize);
    this->m_queueLogs2.reserve(this->defaultQueueSize);
}
