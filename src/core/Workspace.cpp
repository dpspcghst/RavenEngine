// workspace.cpp

#include <iostream>
#include <glad/glad.h>
#include "MenuSystem.h"
#include "Workspace.h"
#include "Console.h"

namespace RavenEngine {

Workspace::Workspace(GLFWwindow* mainWindow)
        : window(mainWindow), 
            settingsManager(SettingsManager::GetInstance()), 
            viewport(window),
            doodleManager(),
            sceneManager(),
            shaderManager(ShaderManager::GetInstance()),  // ShaderManager instance obtained
            uiManager(doodleManager, viewport, shaderManager),  // Passing ShaderManager by reference
            menuSystem(*this, mainWindow, doodleManager, uiManager) {
        
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = nullptr;

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
