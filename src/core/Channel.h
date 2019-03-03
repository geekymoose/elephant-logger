#pragma once

#include <vector>

#include "elephantlogger/outputs/IOutput.h"
#include "elephantlogger/core/LogMessage.h"


namespace elephantlogger {


/**
 * A Channel is where logs are sent.
 * Several outputs may be registered for a channel.
 * Writting in a channel writes in all registered outputs for this channel.
 */
class Channel {
    private:
        std::vector<IOutput *> m_outputs;

    public:
        Channel() = default;
        ~Channel() = default;

        /**
         * A an output linked with this Channel.
         * Channel now write in this output as well.
         *
         * \param output Pointer to the output.
         */
        void addOutput(IOutput * output) {
            m_outputs.push_back(output);
        }

        /**
         * Write message in all outputs linked with this channel.
         *
         * \param message Log message to write.
         */
        void write(const LogMessage & message) {
            for(auto it = m_outputs.begin(); it != m_outputs.end(); ++it) {
                (*it)->write(message);
            }
        }
};


} // End namespace
