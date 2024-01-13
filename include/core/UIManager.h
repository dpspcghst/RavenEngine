#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "Console.h"          
#include "../Scene/SceneHierarchyPanel.h"
#include "../Scene/SceneManager.h"
#include "Viewport.h"

namespace RavenEngine {
    class Console;
    class SceneHierarchyPanel;
    class SceneManager;
}

class UIManager {
public:
    UIManager(RavenEngine::Viewport& viewport); // Add a Viewport reference to the constructor
    
    // Set the current SceneManager context for the hierarchy panel
    void SetSceneManagerContext(RavenEngine::SceneManager* sceneManager);

    // Render UI components
    void Render();

    // Add a log message to the console
    void AddLogToConsole(const std::string& message);

private:
    RavenEngine::Console console;
    RavenEngine::SceneHierarchyPanel sceneHierarchyPanel;
    RavenEngine::Viewport& viewport; // Add a Viewport reference as a member variable
};

#endif // UI_MANAGER_H