#pragma once
#include <string>
#include <nlohmann/json.hpp>

namespace RavenEngine {

class SettingsManager {
public:
    // Constructor
    SettingsManager(const std::string& filePath = SETTINGS_FILE_PATH);

    // Methods for loading settings from a file
    bool LoadSettings(const std::string& filePath);

    // Getter methods for retrieving settings
    std::string GetGameTitle() const;
    int GetResolutionWidth() const;
    int GetResolutionHeight() const;
    std::string GetRenderStyle() const;
    std::string GetCreatorName() const;

    // Setter methods for changing settings
    void SetGameTitle(const std::string& title);
    void SetResolutionWidth(int width);
    void SetResolutionHeight(int height);
    void SetRenderStyle(const std::string& style);
    void SetCreatorName(const std::string& name);

    // Constants for the JSON keys
    static constexpr const char* SCREEN_WIDTH = "width";
    static constexpr const char* SCREEN_HEIGHT = "height";

private:
    // Constant for the default settings file path
    static constexpr const char* SETTINGS_FILE_PATH = "ProjectSettings.json";

    // Member to store the settings
    nlohmann::json settingsJson;
};

} // namespace RavenEngine