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
                     SceneManager& sceneManager, ShaderManager& shaderManagerInstance,
                     TextureManager& textureManager, CollisionPanel& collisionPanel)
    : viewport(viewport), doodleManager(doodleManager), paletteManager(paletteManager), 
      calculatorManager(calculatorManager), sceneManager(sceneManager), 
      scenePanel(shaderManagerInstance), 
      inspector(scenePanel, textureManager, collisionPanel, &sceneManager),
      textureManagerPanel(textureManager, [](int){}),
      collisionPanel(collisionPanel) { // Ensure this is correctly initialized
    // Initialization logic here if needed
    scenePanel.SetSize(200, 800);
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
    
    ImGui::SetNextWindowSize(ImVec2(400, 400), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 400, 
                            ImGui::GetIO().DisplaySize.y - 240), ImGuiCond_FirstUseEver); 

    textureManagerPanel.Draw(); // Draw the TextureManagerPanel
}

void UIManager::SetSceneManagerContext(SceneManager* sceneManager) {
    scenePanel.SetSceneManager(sceneManager);
}

} // namespace RavenEngine