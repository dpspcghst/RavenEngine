// workspace.cpp

#include <iostream>
#include <glad/glad.h>
#include "MenuSystem.h"
#include "Workspace.h"
#include "Console.h"

namespace RavenEngine {

Workspace::Workspace(GLFWwindow* mainWindow)
        : window(mainWindow), 
            viewport(window),
            doodleManager(),
            sceneManager(),
            uiManager(doodleManager, paletteManager, calculatorManager, viewport, ShaderManager::GetInstance(), sceneManager, TextureManager::GetInstance()),  // Use singleton instances
            menuSystem(*this, mainWindow, doodleManager, paletteManager, calculatorManager, uiManager) {
        
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;

        console.AddLog("Welcome to RavenEngine!");

        uiManager.SetSceneManagerContext(&sceneManager);
}

void Workspace::Render() {
    //std::cout << "Rendering Workspace..." << std::endl;

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    menuSystem.createMainMenu();
    //std::cout << "main menu created" << std::endl;
    uiManager.Render();

    glDisable(GL_BLEND);
}

void Workspace::Update() {
    // Update logic here
}

} // namespace RavenEngine
