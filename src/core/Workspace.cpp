#include <glad/glad.h>
#include "Workspace.h"
#include <iostream>
#include "ComponentCreator.h"
#include "MenuSystem.h"

namespace RavenEngine {

Workspace::Workspace(GLFWwindow* mainWin)
    : window(mainWin), viewport(mainWin), doodleManager(), 
      uiManager(viewport, doodleManager), sceneManager(), 
      componentManager(), menuSystem(*this, mainWin, doodleManager, uiManager) {
    std::cout << "Initializing Workspace..." << std::endl;
    
    // Disable .ini file handling for ImGui
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;

    // Set the context for the UIManager
    uiManager.SetSceneManagerContext(&sceneManager);
    uiManager.AddLogToConsole("Workspace initialized successfully.");
}

void Workspace::Render() {
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    componentManager.RenderImGuiComponents();
    menuSystem.createMainMenu(); // Render the menu using MenuSystem
    uiManager.Render();

    glDisable(GL_BLEND);
}

void Workspace::AddComponent(const std::string& componentName) {
    std::cout << "Adding component: " << componentName << std::endl;
    auto newComponent = ComponentCreator::CreateComponent(componentName, 0.0f, 0.0f, 100.0f, 100.0f);
    if (newComponent) {
        componentManager.AddComponent(std::move(newComponent));
        std::cout << "Component added successfully." << std::endl;
    } else {
        std::cerr << "Failed to create component: " << componentName << std::endl;
    }
}

void Workspace::Update() {
    componentManager.UpdateComponents();
    // Additional update logic can be placed here if needed
}

} // namespace RavenEngine