#pragma once
#include <fstream>


namespace ElephantLogger {


/**
 * Abstract class that defines where a Log Output.
 * It is a console where logs are printed.
 *
 * \remark
 * Output may be linked with a file.
 * In that case, logs may be also written in this file.
 *
 * \note
 *  To create your own new LogOutput implementation.
 *      -# Create a new LogOuputX that inherits this class.
 *      -# Add a new value in the LogOutputType enum.
 *      -# Register this Output in the LoggerManager.
 *      -# Add a new macro that calls this output.
 *
 * \author  Constantin Masson
 * \since   1.0
 */
class LogOutput {

    protected:
        /** Full path of the log file (path + name + ext). */
        std::string m_pathLogFile;

        /**
         * Stream used to write in file.
         * If a log file is set, this stream is open (With the logFilePath).
         */
        std::ofstream m_fileOutputStream;


    protected:

        /**
         * Creates a new LogChannel (Not linked with a file).
         */
        LogOutput() = default;

        /**
         * Creates a new LogChannel linked with the given file.
         */
        LogOutput(std::string const& filePath);

    public:
        virtual ~LogOutput();


    // -------------------------------------------------------------------------
    // Print Methods
    // -------------------------------------------------------------------------
    public:
        /**
         * Write a message on this output and add a line return.
         * Message is printed as it is (Not format added, only a line return).
         *
         * \param message The message to print in the channel.
         */
        virtual void print(std::string const& message) const = 0;


    // -------------------------------------------------------------------------
    // File Methods
    // -------------------------------------------------------------------------
    public:

        /**
         * Write a message in the linked file and add a line return.
         * Message is printed as it is (Not format added etc).
         *
         * \remark
         * Do nothing if no file linked.
         *
         * \param message The message to print in the channel.
         */
        void writeInFile(std::string const& message);

        /**
         * Links this Output with the given file.
         * A stream is opened on this file path (append mode).
         * The path part must exists, otherwise, link fails.
         *
         * \return True if successuflly linked, otherwise, return false.
         */
        bool linkWithFile(std::string const& filePath);

        /**
         * Remove the link with a file and close the file stream.
         * Disable all operations on this Output's file.
         */
        void unlinkFile();
};


} // End namespace
