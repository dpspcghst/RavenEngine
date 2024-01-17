#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <GLFW/glfw3.h>
#include "UIManager.h"
#include "Viewport.h"
#include "Scene/SceneManager.h"
#include "../Components/ComponentManager.h"
#include "../utils/Doodle/DoodleManager.h"
#include "../utils/MenuSystem.h"
#include "SettingsManager.h" // Include the SettingsManager header

namespace RavenEngine {
    class SceneManager;

    class Workspace {
    public:
        Workspace(GLFWwindow* mainWin, SettingsManager& settingsManager); // Add SettingsManager to the constructor
        void Render();
        void AddComponent(const std::string& componentName);
        void Update();

    private:
        GLFWwindow* window;
        UIManager uiManager;
        Viewport viewport; // Viewport now requires a SettingsManager object
        SceneManager sceneManager;
        ComponentManager componentManager;
        DoodleManager doodleManager;
        MenuSystem menuSystem;  // Add MenuSystem as a member variable
        SettingsManager& settingsManager; // Add SettingsManager as a member variable
    };
}

#endif // WORKSPACE_H