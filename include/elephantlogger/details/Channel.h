#pragma once

#include <vector>

#include "elephantlogger/outputs/IOutput.h"
#include "LogMessage.h"


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

        /**
         * Add an output in this channel.
         * This channel now writes in this output as well.
         *
         * \param output Pointer to the output.
         */
        void addOutput(IOutput * output) {
            m_outputs.push_back(output);
        }

        /**
         * Writes the message in the channel's outputs.
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
