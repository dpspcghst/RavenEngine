// SettingsManager.cpp

// Primarily used for setting/getting Project Settings.

// #include section
// #################
// Standard library includes
#include <fstream>
#include <iostream>

// Project includes
#include "SettingsManager.h"

namespace RavenEngine {

SettingsManager::SettingsManager(const std::string& filePath) {          // Constructor
    //std::cout << "SettingsManager constructor called" << std::endl;      // Output "SettingsManager constructor called"
    //std::cout << "filePath: " << filePath << std::endl;                      // Output "filePath: " + filePath
    // Constructor logic, if any
    LoadSettings(filePath);
}

SettingsManager::~SettingsManager() {                                    // Destructor
    // Destructor logic, if any
}

bool SettingsManager::LoadSettings(const std::string& filePath) {        // Load settings from file
    //std::cout << "loadsettings called" << std::endl;                     // Output "loadsettings called

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open settings file: " << filePath << std::endl;
        return false;
    }

    try {
        file >> settingsJson;
    } catch (const std::exception& e) {
        std::cerr << "Error reading settings file: " << e.what() << std::endl;
        file.close();
        return false;
    }

    file.close();
    return true;
}

std::string SettingsManager::GetGameTitle() const {                      // GameTitle Getter
    return settingsJson.at("gameTitle").get<std::string>();
}

void SettingsManager::SetGameTitle(const std::string& title) {           // GameTitle Setter
    settingsJson["gameTitle"] = title;
}

int SettingsManager::GetResolutionWidth() const {                        // ResolutionWidth Getter
    return settingsJson.at("resolution").at("width").get<int>();
}

void SettingsManager::SetResolutionWidth(int width) {                    // ResolutionWidth Setter
    settingsJson["resolution"]["width"] = width;
}

int SettingsManager::GetResolutionHeight() const {                       // ResolutionHeight Getter
    return settingsJson.at("resolution").at("height").get<int>();
}

void SettingsManager::SetResolutionHeight(int height) {                  // ResolutionHeight Setter
    settingsJson["resolution"]["height"] = height;
}

std::string SettingsManager::GetRenderStyle() const {                    // RenderStyle Getter
    return settingsJson.at("renderStyle").get<std::string>();
}

void SettingsManager::SetRenderStyle(const std::string& style) {         // RenderStyle Setter
    settingsJson["renderStyle"] = style;
}

std::string SettingsManager::GetCreatorName() const {                    // CreatorName Getter
    return settingsJson.at("creatorName").get<std::string>();
}

void SettingsManager::SetCreatorName(const std::string& name) {          // CreatorName Setter
    settingsJson["creatorName"] = name;
}

} // namespace RavenEngine