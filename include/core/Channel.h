#pragma once

#include "output/IOutput.h"

#include <vector>


namespace ElephantLogger {

class LogMessage;


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
};


} // End namespace
