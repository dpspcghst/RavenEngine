// UIManager.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third-party library includes
#include "glad/glad.h"
#include <imgui.h>

// Local project includes
#include "UIManager.h"
#include "Console.h"
#include "Viewport.h"
#include "../../Tools/Doodle/DoodleManager.h"
#include "../utils/Inspector.h"

namespace RavenEngine {
    
UIManager::UIManager(DoodleManager& doodleManager, PaletteManager& paletteManager, 
                     CalculatorManager& calculatorManager, Viewport& viewport, 
                     ShaderManager& shaderManagerInstance, SceneManager& sceneManager,
                     TextureManager& textureManager)  // Added TextureManager parameter
    : viewport(viewport), doodleManager(doodleManager), paletteManager(paletteManager), 
      scenePanel(shaderManagerInstance), sceneManager(sceneManager), 
      inspector(scenePanel, textureManager),  // Now passing TextureManager to Inspector
      calculatorManager(calculatorManager) {
    // initialize ui manager
    scenePanel.SetSize(200, 800);
    //std::cout << "Initializing UIManager..." << std::endl;
}

void UIManager::Render() { // Render the UIManager
                                                                                   
    // Dockspace
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);       // Create a dockspace over the main viewport


    // Doodle window
    doodleManager.Update();

    // Palette window
    paletteManager.Update();

    // Calculator window
    calculatorManager.Update();

    // Console window
    ImGui::SetNextWindowSize(ImVec2(800, 300), ImGuiCond_FirstUseEver);                                   // Set initial console window size                                                                   
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 400, 
                            ImGui::GetIO().DisplaySize.y - 380), ImGuiCond_FirstUseEver);                 // Set initial console window position
    console.Render();

    // Viewport window
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);                                   // Set initial viewport window size
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x / 2 - 400, 
                            ImGui::GetIO().DisplaySize.y - 960), ImGuiCond_FirstUseEver);                 // Set initial viewport window position
    SceneNode& rootNode = sceneManager.GetRootNode();
    viewport.Render(rootNode);  // Pass the root node to viewport.Render                                                                                   // Render the viewport

    // Scene panel window
    ImGui::SetNextWindowSize(ImVec2(200, 800), ImGuiCond_FirstUseEver);                                  // Set initial scene panel window size
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - ImGui::GetIO().DisplaySize.x, 
                            ImGui::GetIO().DisplaySize.y - 960), ImGuiCond_FirstUseEver);                 // Set initial scene panel window position
    scenePanel.OnImGuiRender();                                                                                  // Render the scene panel

    // Inspector window
    inspector.Render(); // Render the Inspector window
}

void UIManager::SetSceneManagerContext(SceneManager* sceneManager) {
    scenePanel.SetSceneManager(sceneManager);
}

} // namespace RavenEngine