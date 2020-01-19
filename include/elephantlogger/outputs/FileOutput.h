#pragma once

#include <string>
#include <fstream>
#include <chrono>
#include <mutex>

#include "IOutput.h"

namespace elephantlogger {


/**
 * This output writes logs in a file.
 * All functions are thread safe.
 */
class FileOutput : public IOutput {

    private:

        std::string m_filename;
        std::ofstream m_stream;
        mutable std::mutex m_streamAccess;

    public:

        /**
         * Creates a new log file (appends log if exists).
         *
         * \param filename File's path (path + name)
         */
        FileOutput(const std::string & filename) : m_filename(filename) {
            m_stream.open(m_filename, std::fstream::app | std::fstream::out); // append
        }

        /**
         * Close file stream and destroye this poor object.
         */
        ~FileOutput() {
            if(m_stream.is_open()) {
                m_stream.close();
            }
        }

        /** \copydoc IOutput::write() */
        void write(const LogMessage & message) override {
            std::lock_guard<std::mutex> lock(m_streamAccess);

            if(m_stream.is_open()) {
                m_stream << message.getFormattedMessage() << std::endl;
            }
        }
};


} // End namespace

