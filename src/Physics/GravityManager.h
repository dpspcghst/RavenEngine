// GravityManager.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <string>
#include <vector>
// Third party includes

// Raven includes

namespace RavenEngine {
struct GravityPreset {
    std::string name;
    double acceleration; // in m/s^2

    GravityPreset(const std::string& name, double acceleration)
        : name(name), acceleration(acceleration) {}
};

class GravityManager {
public:
    GravityManager() {
        presets.push_back(GravityPreset("Default (Earth)", 9.81));
        presets.push_back(GravityPreset("Sun", 274.0));
        presets.push_back(GravityPreset("Mercury", 3.7));
        presets.push_back(GravityPreset("Venus", 8.87));
        presets.push_back(GravityPreset("Moon", 1.62));
        presets.push_back(GravityPreset("Mars", 3.711));
        presets.push_back(GravityPreset("Jupiter", 24.79));
        presets.push_back(GravityPreset("Saturn", 10.44));
        presets.push_back(GravityPreset("Uranus", 8.69));
        presets.push_back(GravityPreset("Neptune", 11.15));
        presets.push_back(GravityPreset("Pluto<3", 0.62));
        presets.push_back(GravityPreset("Deep Space", 0.0));
        currentGravity = 9.81; // Default to Earth's gravity
    }

    const std::vector<GravityPreset>& GetPresets() const { return presets; }

    std::vector<std::string> GetPresetNames() const {
        std::vector<std::string> names;
        for (const auto& preset : presets) {
            names.push_back(preset.name);
        }
        return names;
    }

    void SetCurrentGravity(double acceleration) { currentGravity = acceleration; }

    void SetCurrentGravity(const std::string& presetName) {
        for (const auto& preset : presets) {
            if (preset.name == presetName) {
                currentGravity = preset.acceleration;
                return;
            }
        }
    }

    double GetCurrentGravity() const { return currentGravity; }

private:
    std::vector<GravityPreset> presets;
    double currentGravity;
};
} // namespace RavenEngine