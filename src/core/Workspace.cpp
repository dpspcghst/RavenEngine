#include <glad/glad.h>
#include "Workspace.h"
#include "UIManager.h"
#include "Viewport.h"
#include <iostream>
#include "ComponentCreator.h"

Workspace::Workspace(GLFWwindow* mainWin)
    : window(mainWin), viewport(mainWin), uiManager(viewport), sceneManager(), componentManager() {
    std::cout << "Initializing Workspace..." << std::endl;
    
    // Set ImGui ini filename to nullptr to disable .ini file saving/loading
    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr; // Add this line to disable .ini file handling

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
    // Update other components as needed
}
