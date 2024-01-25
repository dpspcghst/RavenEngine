// UIManager.cpp

// #include section
// #####################

// Standard library includes
#include <iostream>

// Third-party library includes
#include "glad/glad.h"

// Local project includes
#include "UIManager.h"
#include <imgui.h>
#include "Viewport.h"
#include "../utils/Doodle/DoodleManager.h"
#include "Console.h"

namespace RavenEngine {

UIManager::UIManager(DoodleManager& doodleManager, Viewport& viewport, ShaderManager& shaderManagerInstance)
    : viewport(viewport), doodleManager(doodleManager), scenePanel(shaderManagerInstance){
    // initialize ui manager
    scenePanel.SetSize(200, 800);
    //std::cout << "Initializing UIManager..." << std::endl;
}

void UIManager::Render() {                                                                                // Render the UIManager
    // console out "Rendering UIManager..."
    //std::cout << "Rendering UIManager..." << std::endl;

    // Doodle window
    doodleManager.Update();

    // Console window
    ImGui::SetNextWindowSize(ImVec2(800, 300), ImGuiCond_FirstUseEver);                                   // Set initial console window size                                                                   
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 400, 
                            ImGui::GetIO().DisplaySize.y - 380), ImGuiCond_FirstUseEver);                 // Set initial console window position
    console.Render();
    // output "console complete"
    //std::cout << "console complete" << std::endl;


    // Viewport window
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);                                   // Set initial viewport window size
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 400, 
                            ImGui::GetIO().DisplaySize.y - 960), ImGuiCond_FirstUseEver);                 // Set initial viewport window position
    SceneNode rootNode;  // This should be the root node of your scene
    viewport.Render(rootNode);  // Pass the root node to viewport.Render                                                                                   // Render the viewport
    // output "viewport complete"
    //std::cout << "viewport complete" << std::endl;

    // Scene panel window
    ImGui::SetNextWindowSize(ImVec2(200, 800), ImGuiCond_FirstUseEver);                                  // Set initial scene panel window size
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - ImGui::GetIO().DisplaySize.x, 
                            ImGui::GetIO().DisplaySize.y - 960), ImGuiCond_FirstUseEver);                 // Set initial scene panel window position
    scenePanel.OnImGuiRender();                                                                                  // Render the scene panel
}

void UIManager::SetSceneManagerContext(SceneManager* sceneManager) {
    // output "Setting SceneManager context..."
    //std::cout << "Setting SceneManager context..." << std::endl;
    scenePanel.SetSceneManager(sceneManager);
}

} // namespace RavenEngine