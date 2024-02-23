// GravityPanel.cpp
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes
#include "imgui.h"
// Raven includes
#include "GravityPanel.h"

namespace RavenEngine {
void GravityPanel::Display() {
    // Display gravity settings
    bool isGravityEnabled = shape2D->GetRigidBody()->IsAffectedByGravity();
    if (ImGui::Checkbox("Gravity", &isGravityEnabled)) {
        shape2D->GetRigidBody()->SetAffectedByGravity(isGravityEnabled);
    }

    if (isGravityEnabled) {
        static int currentPreset = 0;
        std::vector<std::string> presetNames = gravityManager.GetPresetNames();
        std::vector<const char*> presetNamesCStr;
        for (const auto& name : presetNames) {
            presetNamesCStr.push_back(name.c_str());
        }
        int presetNamesSize = static_cast<int>(presetNamesCStr.size()); // Convert size_t to int
        if (ImGui::Combo("Gravity Presets", &currentPreset, presetNamesCStr.data(), presetNamesSize)) {
            gravityManager.SetCurrentGravity(presetNames[currentPreset]);
        }

        static float customGravity = static_cast<float>(gravityManager.GetCurrentGravity());
        if (ImGui::SliderFloat("Custom Gravity", &customGravity, 0.0f, 100.0f)) {
            gravityManager.SetCurrentGravity(customGravity);
        }
    }
}
} // namespace RavenEngine