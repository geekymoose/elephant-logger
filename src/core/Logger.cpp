#include "Logger.h"


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

    LoggerConfig conf;
    conf.setDefaultConfig();
    this->applyConfig(conf);

    // TODO To move
    // Set default outputs
    static LogFile      generalFile(this->m_logFilePath, "logs.log");
    static ConsoleCout  coutConsole;
    static LogFile      coutFile(this->m_logFilePath, "cout.log");
    static ConsoleVS    visualConsole;
    static LogFile      visualFile(this->m_logFilePath, "vs.log");

    this->addOutput(0, &coutConsole);
    this->addOutput(0, &coutFile);
    this->addOutput(1, &visualConsole);
    this->addOutput(1, &visualFile);
    this->addOutput(3, &generalFile);

    if(this->m_clearAtStart) {
        for(int k = 0; k < this->m_nbChannels; ++k) {
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
                      va_list argList) {
    if (this->m_isRunning) {
        std::lock_guard<std::mutex> lock(m_queuesFrontAccessMutex);
        this->m_queueLogsFront->emplace_back(level, channelID, file, line, function, format, argList);
    }
}

void Logger::saveAllLogs() const {
    for(int k = 0; k < this->m_nbChannels; ++k) {
        this->m_lookupChannels[k]->save();
    }
}


// -----------------------------------------------------------------------------
// Internal Methods
// -----------------------------------------------------------------------------

void Logger::internalProcessBackQueue() {
    for (LogMessage& msg : *this->m_queueLogsBack) {
        int index = msg.getChannelID();
        if(index < this->m_nbChannels) {
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
                    this->m_threadUpdateRate
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

bool Logger::isAcceptedLogLevel(const LogLevel level) const {
    return this->m_currentLogLevel >= level;
}

void Logger::setLogLevel(const LogLevel level) {
    this->m_currentLogLevel = static_cast<int8_t>(level);
}

LogLevel Logger::getLogLevel() const {
    return static_cast<LogLevel>(this->m_currentLogLevel.load());
}

void Logger::addOutput(const int channelID, IOutput* output) {
    if(channelID >= 0 && channelID < this->m_nbChannels) {
        this->m_lookupChannels[channelID]->addOutput(output);
    }
}

void Logger::applyConfig(const LoggerConfig& config) {
    this->setLogLevel(config.logLevel);
    this->m_nbChannels      = config.nbChannels;
    this->m_logFilePath     = config.logFilePath;
    this->m_threadUpdateRate= config.threadUpdateRate;
    this->m_clearAtStart    = config.clearAtStart;
    this->m_defaultQueueSize= config.defaultQueueSize;

    for(int k = 0; k < this->m_nbChannels; ++k) {
        this->m_lookupChannels[k] = std::unique_ptr<Channel>(new Channel());
    }

    this->m_queueLogs1.reserve(this->m_defaultQueueSize);
    this->m_queueLogs2.reserve(this->m_defaultQueueSize);
}
