#pragma once

#include <mutex>
#include <string>
#include <fstream> //for ofstream
#include <chrono>

#include "IOutput.h"
#include "elephantlogger/core/LogMessage.h"

namespace elephantlogger {


/**
 * IOutput implementation for logs in files.
 *
 * All functions are thread safe.
 */
class LogFile : public IOutput {

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
        LogFile(const std::string & filename) : m_filename(filename) {
            this->m_stream.open(m_filename);
        }

        /**
         * Close file stream and destroye this poor object.
         */
        ~LogFile() {
            if(this->m_stream.is_open()) {
                this->m_stream.close();
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

        /**
         * Save the content of the log file.
         * Place the copy in the given path.
         *
         * \return True if saved successfully, otherwise, return false.
         */
        bool save(const char* path) const {
            /* TODO
            std::lock_guard<std::mutex> lock(m_streamAccess);

            if(this->m_stream.is_open()) {
                using Clock = std::chrono::system_clock;
                std::time_t startTime = Clock::to_time_t(Clock::now());

                char timestamp[20];
                std::strftime(timestamp, 20, "%Y_%m_%d_%H%M%S", std::localtime(&startTime));

                return this->internal_save(path, timestamp);
                // std::string fullSavePath = std::string(path) 
                // + "/" + timestamp + "_" + this->m_fileName;
            }
            */
           return false; // TODO TMP
        }
};


} // End namespace

