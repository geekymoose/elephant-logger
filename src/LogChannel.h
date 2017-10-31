#pragma once


namespace MoonRPG
{


    /**
     * Abstract class that defines a log channel.
     * A log channel is an output where logs can be displayed.
     *
     * \remark
     * All available log channels are listed in the LogChannel::Output enum.
     * To reference the channel COCO, use LogChannel::COCO .
     *
     * \remark
     * Channel may be linked with a file.
     *
     * \note
     * HOW TO ADD A NEW LOG CHANNEL IN YOUR LOGGERS LIST:
     *  inherit this class,
     *  add new constant in LogChannel::Output,
     *  register this new channel in the LoggerManager.
     */
    class LogChannel
    {
        public:
            /** List of available channels. */
            enum Output
            {
                Vs,         // Visual Studio
                Cout        // Simple std::cout
            };


        protected:
            /** Full path of the log file (path + name + ext). */
            std::string m_pathLogFile;

            /**
             * Stream used to write in file.
             * If a log file is set, this stream is open (With the logFilePath).
             */
            std::ofstream m_fileOutputStream;


        protected:
            // -----------------------------------------------------------------
            // Output methods
            // -----------------------------------------------------------------

            /** Creates a new LogChannel (Not linked with a file) */
            LogChannel() = default;

            /** Creates a new LogChannel linked with the given file */
            LogChannel(std::string const& filePath);

        public:
            virtual ~LogChannel();


        public:
            /**
             * Write a message in this channel and add a line return.
             * Message is printed as it is.
             *
             * \param message The message to print in the channel.
             */
            virtual void writeInChannel(std::string const& message) const = 0;


        public:
            // -----------------------------------------------------------------
            // Methods for file
            // -----------------------------------------------------------------

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
             * Links this LogChannel with the given file.
             * A stream is opened on this file path (append mode).
             * The path part must exists, otherwise, link fails.
             *
             * \return True if successuflly linked, otherwise, return false.
             */
            bool linkWithFile(std::string const& filePath);

            /**
             * Remove the link with a file and close the file stream.
             * Disable all operations on this LogChannel's file.
             */
            void unlinkFile();
    };


    // -------------------------------------------------------------------------
    // LogChannel implementations
    // -------------------------------------------------------------------------

    /**
     * LogChannel implementation for Visual Studio output.
     */
    class LogChannelVS : public LogChannel
    {
        public:
            LogChannelVS() : LogChannel() {};
            LogChannelVS(std::string const& filePath) : LogChannel(filePath) {};
        public:
            void writeInChannel(std::string const& message) const override;
    };

    /**
     * LogChannel implementation for std::cout output.
     */
    class LogChannelCout : public LogChannel
    {
        public:
            LogChannelCout() : LogChannel() {};
            LogChannelCout(std::string const& filePath) : LogChannel(filePath) {};
        public:
            void writeInChannel(std::string const& message) const override;
    };


} // End MoonRPG namespace