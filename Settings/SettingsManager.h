// settingsmanager.h
// #####################
#pragma once
// #####################

// Standard library includes
#include <string> // For std::string

// Third-party includes
#include <nlohmann/json.hpp> // For nlohmann::json

// Raven includes

namespace RavenEngine {

// Class: SettingsManager
// Description: Manages the settings of the game engine
class SettingsManager {
public:
    // Deleted copy constructor and assignment operator
    SettingsManager(SettingsManager const&) = delete;
    void operator=(SettingsManager const&) = delete;

    // Function to get the singleton instance
    static SettingsManager& GetInstance() {
        static SettingsManager instance;
        return instance;
    }

    // Function: LoadSettings
    // Description: Loads settings from a JSON file
    // Parameters: filePath - The path to the JSON file
    // Returns: true if the settings were loaded successfully, false otherwise
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

    float GetFrameRate() const; // FrameRate Getter
    void SetFrameRate(float frameRate); // FrameRate Setter


    // Constants for the JSON keys
    static constexpr const char* SCREEN_WIDTH = "width";
    static constexpr const char* SCREEN_HEIGHT = "height";

private:
    // Private constructor
    SettingsManager(const std::string& filePath = SETTINGS_FILE_PATH);
    // Private destructor
    ~SettingsManager();

    // Constant for the default settings file path
    static constexpr const char* SETTINGS_FILE_PATH = "D:/RavenEngineProject/RavenEngine/Settings/ProjectSettings.json";

    // Member to store the settings
    nlohmann::json settingsJson;
};

} // namespace RavenEngine