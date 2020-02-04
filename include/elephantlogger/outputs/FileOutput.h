#pragma once

#include <string>
#include <fstream>
#include <chrono>
#include <mutex>

#include "LogOutput.h"

namespace elephantlogger {

class FileOutput : public LogOutput {

    private:

        std::string m_filename;
        std::ofstream m_stream;
        mutable std::mutex m_streamAccess;

    public:

        FileOutput(const std::string & filename) : m_filename(filename) {
            m_stream.open(m_filename, std::fstream::app | std::fstream::out); // Append if exists
        }

        ~FileOutput() {
            if(m_stream.is_open()) {
                m_stream.close();
            }
        }

        void write(const LogMessage & message) override {
            std::lock_guard<std::mutex> lock(m_streamAccess);

            if(m_stream.is_open()) {
                m_stream << message.getFormattedMessage() << std::endl;
            }
        }
};


}

