// workspace.h

#ifndef WORKSPACE_H
#define WORKSPACE_H

// #include section
// #####################
// Third-party includes
#include <GLFW/glfw3.h>

// Local project includes
#include "SettingsManager.h"
#include "UIManager.h"
#include "Viewport.h"
#include "../../src/Scene/SceneManager.h"
#include "../utils/Doodle/DoodleManager.h"
#include "../utils/MenuSystem.h"
#include "../Assets/Shaders/ShaderManager.h"

namespace RavenEngine {
    class SceneManager;

    class Workspace {
    public:
        Workspace(GLFWwindow* mainWindow); 
        void Render();
        void Update();

    private:
        GLFWwindow* window;
        UIManager uiManager;
        Viewport viewport;
        SceneManager sceneManager;
        DoodleManager doodleManager;
        MenuSystem menuSystem;
        SettingsManager& settingsManager;
        ShaderManager& shaderManager;
    };
}

#endif // WORKSPACE_H