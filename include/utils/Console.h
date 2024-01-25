// console.h
#pragma once

// include section
// #####################
// Standard library includes
#include <string>
#include <vector>

// Third-party libraries
#include "imgui.h"

namespace RavenEngine {

class Console {
public:
    Console();
    ~Console();

    void AddLog(const std::string& message); // Add a log message
    void Render(bool* p_open = nullptr); // Render the console window

private:
    std::vector<std::string> log; // Stores all the log messages
    // Other members as needed (e.g., command history, input buffer)
};

extern Console console; // Declare a global Console instance (add console.h/ console.AddLog() to use for debugging)

} // namespace RavenEngine