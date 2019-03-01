#pragma once

#include <vector>


namespace elephantlogger {

class LogMessage;
class IOutput;


/**
 * A Channel is where logs are sent.
 * Several outputs may be registered for a channel.
 * Writting in a channel writes in all registered outputs for this channel.
 */
class Channel {
    private:
        std::vector<IOutput*> m_outputs;

    public:
        Channel() = default;
        ~Channel() = default;

    public:

        /**
         * A an output linked with this Channel.
         * Channel now write in this output as well.
         *
         * \param output Pointer to the output.
         */
        void addOutput(IOutput * output);

        /**
         * Write message in all outputs linked with this channel.
         *
         * \param message Log message to write.
         */
        void write(const LogMessage & message);
};


} // End namespace
