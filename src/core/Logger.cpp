#include "Logger.h"

#include <cassert>


using namespace elephantlogger;


// -----------------------------------------------------------------------------
// Init
// -----------------------------------------------------------------------------
Logger::~Logger() {
    this->shutdown();
}

void Logger::startup() {
    assert(this->m_isRunning == false);
    if (this->m_isRunning) {
        return;
    }

    this->m_isRunning           = true;
    this->m_queueLogsFront      = &m_queueLogs1;
    this->m_queueLogsBack       = &m_queueLogs2;
    this->m_queueLogs1          .reserve(config::DEFAULT_QUEUE_SIZE);
    this->m_queueLogs2          .reserve(config::DEFAULT_QUEUE_SIZE);

    assert(this->m_queueLogsFront != nullptr);
    assert(this->m_queueLogsBack  != nullptr);

    for(int k = 0; k < config::NB_CHANNELS; ++k) {
        this->m_lookupChannels[k] = std::unique_ptr<Channel>(new Channel());
        if(config::CLEAR_AT_START) {
            assert(this->m_lookupChannels[k] != nullptr);
            this->m_lookupChannels[k]->clear();
        }
    }

    this->runInThread();
}

void Logger::shutdown() {
    this->swapQueues();
    this->processBackQueue();
    this->swapQueues();
    this->processBackQueue();
    this->m_isRunning = false;
}


// -----------------------------------------------------------------------------
// Core Methods
// -----------------------------------------------------------------------------

void Logger::queueLog(const LogLevel level,
                      const int channelID,
                      const char* file,
                      const int line,
                      const char* function,
                      const char* format,
                      va_list argList) {

    std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);

    if (this->m_isRunning) {
        this->m_queueLogsFront->emplace_back(
                level, channelID, file, line, function, format, argList);
    }
}

void Logger::saveAllLogs(const char* path) const {
    for(int k = 0; k < config::NB_CHANNELS; ++k) {
        assert(this->m_lookupChannels[k] != nullptr);
        this->m_lookupChannels[k]->save(path);
    }
}


// -----------------------------------------------------------------------------
// Internal Methods
// -----------------------------------------------------------------------------

void Logger::processBackQueue() {
    std::lock_guard<std::mutex> lock(m_queuesBackAccessMutex);

    for (LogMessage& msg : *this->m_queueLogsBack) {

        int channelID = msg.getChannelID();
        assert(channelID < config::NB_CHANNELS);

        if(channelID < config::NB_CHANNELS) {
            auto& coco = m_lookupChannels[static_cast<size_t>(channelID)];
            coco->write(msg);
        }
    }
    this->m_queueLogsBack->clear();
}

void Logger::swapQueues() {
    std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);
    std::lock_guard<std::mutex> lock2(m_queuesBackAccessMutex);
    std::swap(this->m_queueLogsFront, this->m_queueLogsBack);
}

void Logger::run() {
    while (this->m_isRunning) {
        std::this_thread::sleep_for(std::chrono::milliseconds{
                config::THREAD_UPDATE_RATE
        });
        this->processBackQueue();
        this->swapQueues();
    }
}

void Logger::runInThread() {
    std::thread {
        [this]() {
            this->run();
        }
    }.detach();
}


// -----------------------------------------------------------------------------
// Getter - Setters
// -----------------------------------------------------------------------------

bool Logger::isAcceptedLogLevel(const LogLevel level) const {
    return this->m_currentLogLevel >= level;
}

void Logger::addOutput(const int channelID, IOutput* output) {
    assert(output != nullptr);
    assert(channelID >= 0 && channelID < config::NB_CHANNELS);
    if(channelID >= 0 && channelID < config::NB_CHANNELS) {
        this->m_lookupChannels[channelID]->addOutput(output);
    }
}

void Logger::setLogLevel(const LogLevel level) {
    this->m_currentLogLevel = static_cast<int>(level);
}

LogLevel Logger::getLogLevel() const {
    return static_cast<LogLevel>(this->m_currentLogLevel.load());
}
