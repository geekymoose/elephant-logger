#include "Channel.h"
#include "elephantlogger/outputs/IOutput.h"

namespace elephantlogger {


void Channel::addOutput(IOutput* output) {
    m_outputs.push_back(output);
}

void Channel::write(const LogMessage & message) {
    for(auto it = m_outputs.begin(); it != m_outputs.end(); ++it) {
        (*it)->write(message);
    }
}


} // End namespace

