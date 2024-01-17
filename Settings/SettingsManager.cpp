#include "SettingsManager.h"
#include <fstream>
#include <iostream>

namespace RavenEngine {

SettingsManager::SettingsManager(const std::string& filePath) {
    // Constructor logic, if any
    LoadSettings(filePath);
}

bool SettingsManager::LoadSettings(const std::string& filePath) {
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

std::string SettingsManager::GetGameTitle() const {
    return settingsJson.at("gameTitle").get<std::string>();
}

void SettingsManager::SetGameTitle(const std::string& title) {
    settingsJson["gameTitle"] = title;
}

int SettingsManager::GetResolutionWidth() const {
    return settingsJson.at("resolution").at("width").get<int>();
}

void SettingsManager::SetResolutionWidth(int width) {
    settingsJson["resolution"]["width"] = width;
}

int SettingsManager::GetResolutionHeight() const {
    return settingsJson.at("resolution").at("height").get<int>();
}

void SettingsManager::SetResolutionHeight(int height) {
    settingsJson["resolution"]["height"] = height;
}

std::string SettingsManager::GetRenderStyle() const {
    return settingsJson.at("renderStyle").get<std::string>();
}

void SettingsManager::SetRenderStyle(const std::string& style) {
    settingsJson["renderStyle"] = style;
}

std::string SettingsManager::GetCreatorName() const {
    return settingsJson.at("creatorName").get<std::string>();
}

void SettingsManager::SetCreatorName(const std::string& name) {
    settingsJson["creatorName"] = name;
}

} // namespace RavenEngine