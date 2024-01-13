#include "glad/glad.h"
#include "UIManager.h"
#include <imgui.h>
#include "Viewport.h"
#include "../utils/Doodle/DoodleManager.h"

namespace RavenEngine {

UIManager::UIManager(Viewport& viewport, DoodleManager& doodleManager)
    : viewport(viewport), doodleManager(doodleManager) {
    // Initialization code for UIManager
    // This could include initializing the Console, SceneHierarchyPanel, etc.
}

void UIManager::Render() {
    // Render the UI components

    // SceneHierarchyPanel window (top-left)
    ImGui::SetNextWindowPos(ImVec2(0, 60), ImGuiCond_FirstUseEver);
    sceneHierarchyPanel.OnImGuiRender();

    // Console window (bottom)
    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - 200), ImGuiCond_FirstUseEver);
    bool consoleWindowOpen = true;
    console.Draw("Console", &consoleWindowOpen);

    // Viewport window (center-right-top)
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, 0), ImGuiCond_FirstUseEver);
    viewport.Render();

    doodleManager.Update();
}

void UIManager::SetSceneManagerContext(SceneManager* sceneManager) {
    sceneHierarchyPanel.SetContext(sceneManager);
}

void UIManager::AddLogToConsole(const std::string& message) {
    console.AddLog(message);
}

// Additional methods for UIManager can be implemented as needed

} // namespace RavenEngine
