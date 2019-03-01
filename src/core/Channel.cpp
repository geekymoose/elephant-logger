#include "Channel.h"
#include "elephantlogger/outputs/IOutput.h"

namespace elephantlogger {


void Channel::addOutput(IOutput* output) {
    this->m_outputs.push_back(output);
}

void Channel::write(const LogMessage & message) {
    std::vector<IOutput*>::iterator it = this->m_outputs.begin();
    for(; it != this->m_outputs.end(); ++it) {
        (*it)->write(message);
    }
}


} // End namespace

