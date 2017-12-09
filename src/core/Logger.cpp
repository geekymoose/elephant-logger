#include "Logger.h"

#include <cassert>


using namespace elephantlogger;


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
    this->m_queueLogs1          .reserve(this->m_defaultQueueSize);
    this->m_queueLogs2          .reserve(this->m_defaultQueueSize);

    this->m_defaultQueueSize    = DEFAULT_QUEUE_SIZE;
    this->m_currentLogLevel     = DEFAULT_LOGLEVEL;
    this->m_clearAtStart        = DEFAULT_CLEAR_AT_START;

    for(int k = 0; k < NB_CHANNELS; ++k) {
        this->m_lookupChannels[k] = std::unique_ptr<Channel>(new Channel());
        if(this->m_clearAtStart) {
            assert(this->m_lookupChannels[k] != nullptr);
            this->m_lookupChannels[k]->clear();
        }
    }

    this->runInThread();
}

void Logger::shutdown() {
    this->m_isRunning = false;
    this->swapQueues();
    this->processBackQueue();
    this->swapQueues();
    this->processBackQueue();
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
        this->m_queueLogsFront->emplace_back(level, channelID, file, line, function, format, argList);
    }
}

void Logger::saveAllLogs(const char* path) const {
    for(int k = 0; k < NB_CHANNELS; ++k) {
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
        assert(channelID < NB_CHANNELS);
        if(channelID < NB_CHANNELS) {
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
            this->m_threadUpdateRate
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
    assert(channelID >= 0 && channelID < NB_CHANNELS);
    if(channelID >= 0 && channelID < NB_CHANNELS) {
        this->m_lookupChannels[channelID]->addOutput(output);
    }
}

void Logger::setLogLevel(const LogLevel level) {
    this->m_currentLogLevel = static_cast<int8_t>(level);
}

LogLevel Logger::getLogLevel() const {
    return static_cast<LogLevel>(this->m_currentLogLevel.load());
}
