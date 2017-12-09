#include "Channel.h"
#include "elephantlogger/outputs/IOutput.h"

using namespace elephantlogger;


void Channel::addOutput(IOutput* output) {
    this->m_outputs.push_back(output);
}

void Channel::write(const LogMessage & message) {
    std::vector<IOutput*>::iterator it = this->m_outputs.begin();
    for(; it != this->m_outputs.end(); ++it) {
        (*it)->write(message);
    }
}

void Channel::save(const char* path) {
    std::vector<IOutput*>::iterator it = this->m_outputs.begin();
    for(; it != this->m_outputs.end(); ++it) {
        (*it)->save(path);
    }
}

void Channel::clear() {
    std::vector<IOutput*>::iterator it = this->m_outputs.begin();
    for(; it != this->m_outputs.end(); ++it) {
        (*it)->clear();
    }
}

void Channel::flush() {
    std::vector<IOutput*>::iterator it = this->m_outputs.begin();
    for(; it != this->m_outputs.end(); ++it) {
        (*it)->flush();
    }
}
