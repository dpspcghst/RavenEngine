// uimanager.h
#ifndef UI_MANAGER_H
#define UI_MANAGER_H
// #include section
// #####################
// Standard library includes

// Third-party libraries

// Raven project includes
#include "Console.h"
#include "../../src/Scene/ScenePanel.h"
#include "../../src/Scene/SceneManager.h"
#include "Viewport.h"
#include "../../Tools/Doodle/DoodleManager.h"
#include "../../Tools//Palette/PaletteManager.h"
#include "../../Tools//Calc/CalculatorManager.h" 
#include "../utils/Inspector.h" 
#include "../../src/Renderer/Texture/TextureManagerPanel.h"
#include "../../src/Physics/CollisionPanel.h"
#include "../../src/Renderer/Shaders/ShaderManager.h"


namespace RavenEngine {
    // Forward declarations
    class ScenePanel;
    class SceneManager;
    class DoodleManager;
    class CalculatorManager;
    class PaletteManager;
    class Inspector;
    

    class UIManager {
    public:
        UIManager(DoodleManager& doodleManager, PaletteManager& paletteManager, 
              CalculatorManager& calculatorManager, Viewport& viewport, 
              SceneManager& sceneManager, ShaderManager& shaderManagerInstance, 
              TextureManager& textureManager, 
              CollisionPanel& collisionPanel);  // Constructor
        void SetSceneManagerContext(SceneManager* sceneManager); // Set the SceneManager context for the UIManager
        void Render(); // Render the UIManager

    private:
        ScenePanel scenePanel; // Scene Panel
        Viewport& viewport; // Viewport
        DoodleManager& doodleManager; // Doodle
        PaletteManager& paletteManager; // Palette
        SceneManager& sceneManager; // SceneManager
        Inspector inspector; // Inspector
        CalculatorManager& calculatorManager; // Calculator
        TextureManagerPanel textureManagerPanel; // TextureManagerPanel
        CollisionPanel& collisionPanel; // CollisionPanel
    };
}

#endif // UI_MANAGER_H