#pragma once

namespace ElephantLogger {


/**
 * List all implemented type of LogOutput.
 *
 * \author  Constantin Masson
 * \since   1.0
 */
enum class LogOutputType {
    Vs = 0,  // Visual Studio Console
    Cout,    // Simple std::cout


    // Internal
    SIZE    // Enum's size: Number of defined OutputType (TO KEEP LAST).
};


} // End namespace
