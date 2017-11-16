#include "core/Channel.h"


using namespace ElephantLogger;


Channel::Channel() {
    this->m_listOutputs.reserve(3); // Pre-allocate 3 places for output.
}

Channel::~Channel() {
    std::vector<IOutput*>::iterator it = this->m_listOutputs.begin();
    for(it; it != this->m_listOutputs.end(); ++it) {
        (*it)->flush();
    }
}

void Channel::addOutput(IOutput* output) {
    this->m_listOutputs.push_back(output);
}

void Channel::write(const LogMessage & message) {
    std::vector<IOutput*>::iterator it = this->m_listOutputs.begin();
    for(it; it != this->m_listOutputs.end(); ++it) {
        (*it)->write(message);
    }
}


