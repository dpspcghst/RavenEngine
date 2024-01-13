#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "UIManager.h"
#include <imgui.h>
#include "Viewport.h"

UIManager::UIManager(RavenEngine::Viewport& viewport) : viewport(viewport) {
    // Initialization code for UIManager
    // For example, initializing the Console or SceneHierarchyPanel
}

void UIManager::Render() {
    // Render the UI components

    // Set the position for the SceneHierarchyPanel window (top-left)
    ImGui::SetNextWindowPos(ImVec2(0, 60), ImGuiCond_FirstUseEver);
    sceneHierarchyPanel.OnImGuiRender();

    // Set the position for the Console window (bottom)
    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - 200), ImGuiCond_FirstUseEver);
    bool consoleWindowOpen = true; // Or manage this state based on your application's needs
    console.Draw("Console", &consoleWindowOpen);

    // Set the position for the Viewport window (center-right-top)
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2, 0), ImGuiCond_FirstUseEver);
    viewport.Render();
}

// Rest of the UIManager class

void UIManager::SetSceneManagerContext(RavenEngine::SceneManager* sceneManager) {
    // Assuming SceneHierarchyPanel requires a SceneManager reference
    sceneHierarchyPanel.SetContext(sceneManager);
}

void UIManager::AddLogToConsole(const std::string& message) {
    // Assuming Console class has a method to add logs
    console.AddLog(message);
}

// Implement other UIManager methods as needed