#pragma once

#include "IOutput.h"

#include <string>
#include <mutex>
#include <fstream>


namespace ElephantLogger {

class LogMessage;


/**
 * File logging output.
 *
 * \note
 * All functions are thread safe.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Nov 2017
 */
class LogFile : public IOutput {
    private:
        /** Path of the log file (Without it's name). */
        std::string m_filePath;

        /** Name of the log file. */
        std::string m_fileName;

        /** Combination of path + file name. */
        std::string m_fullPath;

        /** Stream to the file. May be opened during all LogFile lifetime. */
        std::ofstream m_stream;

        /** Mutex for thread safe methods. */
        mutable std::mutex m_streamAccess;


    public:

        /**
         * Create a new log file.
         * If filePath doesn't exists, tries to create id. (Parent must exists).
         * If file doesn't exists, create it, otherwise, open it (Append mode).
         *
         * \warning
         * If it's impossible to create the directory,
         * all methods return false and do nothing.
         *
         * \param filePath Directory where file may live.
         * \param fileName Name of the file.
         */
        LogFile(std::string filePath, std::string fileName);

        /**
         * Close file stream and destroye this poor object.
         */
        ~LogFile();


    public:

        /**
         * \copydoc IOutput::write()
         */
        void write(const LogMessage & message) override;

        /**
         * \copydoc IOutput::flush()
         */
        void flush() override;

        /**
         * Save the content of the log file.
         * Copy is placed in the same directory, but with current timestamp suffix.
         *
         * \return True if saved successfully, otherwise, return false.
         */
        bool save() const override;

        /**
         * Clear content of the log file.
         */
        void clear() override;


    private:
        bool internal_save(std::string & savePath) const;
};


} // End namespace
