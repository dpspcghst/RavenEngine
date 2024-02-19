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
#include "../../Tools/Doodle/DoodleManager.h"
#include "../../Tools/Palette/PaletteManager.h"
#include "../../Tools/Calc/Calculator.h"
#include "../utils/MenuSystem.h"
#include "../src/Renderer/Shaders/ShaderManager.h"
#include "../src/Renderer/Texture/TextureManager.h"
#include "../src/Physics/CollisionPanel.h"

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
        PaletteManager paletteManager;
        CalculatorManager calculatorManager;
        MenuSystem menuSystem;
        CollisionPanel collisionPanel;
    };
}

#endif // WORKSPACE_H