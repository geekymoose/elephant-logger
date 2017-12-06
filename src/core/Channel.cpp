#include "elephantlogger/core/Channel.h"
#include "elephantlogger/outputs/IOutput.h"

using namespace elephantlogger;


Channel::Channel() {
    this->m_listOutputs.reserve(3); // Pre-allocate 3 places for output.
}

void Channel::addOutput(IOutput* output) {
    this->m_listOutputs.push_back(output);
}

void Channel::write(const LogMessage & message) {
    std::vector<IOutput*>::iterator it = this->m_listOutputs.begin();
    for(; it != this->m_listOutputs.end(); ++it) {
        (*it)->write(message);
    }
}

void Channel::flush() {
    std::vector<IOutput*>::iterator it = this->m_listOutputs.begin();
    for(; it != this->m_listOutputs.end(); ++it) {
        (*it)->flush();
    }
}

void Channel::save() {
    std::vector<IOutput*>::iterator it = this->m_listOutputs.begin();
    for(; it != this->m_listOutputs.end(); ++it) {
        (*it)->save();
    }
}

void Channel::clear() {
    std::vector<IOutput*>::iterator it = this->m_listOutputs.begin();
    for(; it != this->m_listOutputs.end(); ++it) {
        (*it)->clear();
    }
}
