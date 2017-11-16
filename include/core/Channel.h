#pragma once

#include <vector>


namespace ElephantLogger {

class LogMessage;
class IOutput;


/**
 * A Channel is where logs are send.
 * Several outputs may be registered for a channel.
 * Writing in a channel writes in all registered outputs for this channel.
 *
 * \author  Constantin Masson
 * \since   1.0
 * \date    Nov 2017
 */
class Channel {
    private:
        std::vector<IOutput*> m_listOutputs;


    public:
        Channel();
        ~Channel();


    public:

        /**
         * A an output linked with this Channel.
         * Channel now write in this output as well.
         *
         * \param output Pointer to the output.
         */
        void addOutput(IOutput* output);

        /**
         * Write message in all output linked with this channel.
         *
         * \param message Log message to write.
         */
        void write(const LogMessage & message);

        /**
         * Flush all outputs.
         */
        void flush();

        /**
         * Save all outputs.
         */
        void save();

        /**
         * Clear all outputs.
         */
        void  clear();
};


} // End namespace
