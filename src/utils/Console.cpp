// console.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third-party library includes
#include <imgui.h>

// Local project includes
#include "Console.h"

namespace RavenEngine {

Console console;

Console::Console() {                                                    // Constructor
    // output "Initializing Console..."
    //std::cout << "Initializing Console..." << std::endl;
}

Console::~Console() {                                                   // Destructor
    // Cleanup code here
}

void Console::AddLog(const std::string& message) {
    log.push_back(message);
    //std::cout << "Added message: " << message << ", log size: " << log.size() << std::endl;
}

void Console::Render(bool* p_open) {
    const char* title = "Console";

    if (!ImGui::Begin(title, p_open)) {
        ImGui::End();
        return;
    }

    //std::cout << "Rendering console, log size: " << log.size() << std::endl;

    for (const auto& message : log) {
        ImGui::TextUnformatted(message.c_str());
    }

    ImGui::End();
}

} // namespace RavenEngine