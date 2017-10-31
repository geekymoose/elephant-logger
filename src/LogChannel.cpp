/* -----------------------------------------------------------------------------
 * LogChannel Definitions
 * ----------------------------------------------------------------------------*/

#include "MoonRPGElephantLoggerPch.h"

#include "LogChannel.h"

#include <iostream>

using namespace MoonRPG;


LogChannel::LogChannel(std::string const& filePath)
{
    this->linkWithFile(filePath);
}

LogChannel::~LogChannel()
{
    this->unlinkFile();
}


void LogChannel::writeInFile(std::string const& message)
{
    if (this->m_fileOutputStream.is_open())
    {
        this->m_fileOutputStream << message << std::endl;
    }
}

bool LogChannel::linkWithFile(std::string const& filePath)
{
    if (this->m_fileOutputStream.is_open())
    {
        this->m_fileOutputStream.close();
    }
    this->m_pathLogFile = filePath;
    this->m_fileOutputStream.open(filePath, std::ios::out | std::ios::app);

    return this->m_fileOutputStream.is_open();
}

void LogChannel::unlinkFile()
{
    if (this->m_fileOutputStream.is_open())
    {
        this->m_fileOutputStream.close();
        this->m_pathLogFile.clear();
    }
}


/* -----------------------------------------------------------------------------
 * Special LogChannels Definitions (Children)
 * ---------------------------------------------------------------------------*/

void LogChannelVS::writeInChannel(std::string const& message) const
{
    OutputDebugStringA(static_cast<LPCSTR>(message.c_str()));
    OutputDebugStringA(static_cast<LPCSTR>("\n")); // There is probably a cleaner way
}

void LogChannelCout::writeInChannel(std::string const& message) const
{
    std::cout << message << std::endl;
}