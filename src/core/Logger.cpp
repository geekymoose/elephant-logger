#include "Logger.h"

#include <cassert>


namespace elephantlogger {


// -----------------------------------------------------------------------------
// Init
// -----------------------------------------------------------------------------

Logger::Logger() :
    m_currentLogLevel(config::DEFAULT_LOGLEVEL),
    m_isRunning(false) {
}

Logger::~Logger() {
    shutdown();
}

void Logger::startup() {
    assert(m_isRunning == false);
    if (m_isRunning) {
        return;
    }

    m_isRunning         = true;
    m_queueLogsFront    = &m_queueLogs1;
    m_queueLogsBack     = &m_queueLogs2;
    m_queueLogs1.reserve(config::DEFAULT_QUEUE_SIZE);
    m_queueLogs2.reserve(config::DEFAULT_QUEUE_SIZE);

    assert(m_queueLogsFront != nullptr);
    assert(m_queueLogsBack  != nullptr);

    startBackThread();
}

void Logger::shutdown() {
    m_isRunning = false;
    swapQueues();
    processBackQueue();
    swapQueues();
    processBackQueue();
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

    if (m_isRunning) {
        m_queueLogsFront->emplace_back(
                level, channelID, file, line, function, format, argList);
    }
}


// -----------------------------------------------------------------------------
// Internal Methods
// -----------------------------------------------------------------------------

void Logger::processBackQueue() {
    std::lock_guard<std::mutex> lock(m_queuesBackAccessMutex);

    for (LogMessage& msg : *m_queueLogsBack) {
        int channelID = msg.getChannelID();
        assert(channelID < config::NB_CHANNELS);

        if(channelID < config::NB_CHANNELS) {
            auto& coco = m_lookupChannels[static_cast<size_t>(channelID)];
            coco.write(msg);
        }
    }
    m_queueLogsBack->clear();
}

void Logger::swapQueues() {
    std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);
    std::lock_guard<std::mutex> lock2(m_queuesBackAccessMutex);
    std::swap(m_queueLogsFront, m_queueLogsBack);
}

void Logger::startBackThread() {
    std::thread {
        [this]() {
            while (m_isRunning) {
                // TODO this is ugly. To change with condition var for instance
                std::this_thread::sleep_for(std::chrono::milliseconds{
                        config::THREAD_UPDATE_RATE
                });
                processBackQueue();
                swapQueues();
            }
        }
    }.detach();
}


// -----------------------------------------------------------------------------
// Getter - Setters
// -----------------------------------------------------------------------------

bool Logger::isLogLevelAccepted(const LogLevel level) const {
    return m_currentLogLevel >= level;
}

void Logger::addOutput(const int channelID, IOutput* output) {
    assert(output != nullptr);
    assert(channelID >= 0 && channelID < config::NB_CHANNELS);
    if(channelID >= 0 && channelID < config::NB_CHANNELS) {
        m_lookupChannels[channelID].addOutput(output);
    }
}

void Logger::setLogLevel(const LogLevel level) {
    m_currentLogLevel = static_cast<int>(level);
}

LogLevel Logger::getLogLevel() const {
    return static_cast<LogLevel>(m_currentLogLevel.load());
}


} // End namespace

