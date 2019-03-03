#pragma once

#include <string>
#include <fstream>
#include <chrono>
#include <mutex>

#include "IOutput.h"
#include "elephantlogger/core/LogMessage.h"

namespace elephantlogger {


/**
 * This output writes logs in a file.
 * All functions are thread safe.
 */
class FileOutput : public IOutput {

    // -------------------------------------------------------------------------
    // Variables
    // -------------------------------------------------------------------------
    private:
        std::string m_filename;
        std::ofstream m_stream;
        mutable std::mutex m_streamAccess;


    // -------------------------------------------------------------------------
    // Initialization
    // -------------------------------------------------------------------------
    public:

        /**
         * Create a new log file.
         *
         * \param filename Name of the file.
         */
        FileOutput(const std::string & filename) : m_filename(filename) {
            m_stream.open(m_filename);
        }

        /**
         * Close file stream and destroye this poor object.
         */
        ~FileOutput() {
            if(m_stream.is_open()) {
                m_stream.close();
            }
        }


    // -------------------------------------------------------------------------
    // IOutPut override
    // -------------------------------------------------------------------------
    public:

        /** \copydoc IOutput::write() */
        void write(const LogMessage & message) override {
            std::lock_guard<std::mutex> lock(m_streamAccess);

            if(m_stream.is_open()) {
                m_stream << message.getFormattedMessage() << std::endl;
            }
        }


    // -------------------------------------------------------------------------
    // Extra methods
    // -------------------------------------------------------------------------
    private:

        bool save(const char* path) const {
            /* TODO
            std::lock_guard<std::mutex> lock(m_streamAccess);

            if(m_stream.is_open()) {
                using Clock = std::chrono::system_clock;
                std::time_t startTime = Clock::to_time_t(Clock::now());

                char timestamp[20];
                std::strftime(timestamp, 20, "%Y_%m_%d_%H%M%S", std::localtime(&startTime));

                return internal_save(path, timestamp);
                // std::string fullSavePath = std::string(path) 
                // + "/" + timestamp + "_" + m_fileName;
            }
            */
           return false; // TODO TMP
        }
};


} // End namespace

