// uimanager.h
#ifndef UI_MANAGER_H
#define UI_MANAGER_H
// #include section
// #####################
// Standard library includes

// Third-party libraries

// Local project includes
#include "Console.h"
#include "../../src/Scene/ScenePanel.h"
#include "../../src/Scene/SceneManager.h"
#include "Viewport.h"
#include "../../Tools/Doodle/DoodleManager.h"
#include "../../Tools//Palette/PaletteManager.h"
#include "../../Tools//Calc/CalculatorManager.h" 
#include "../utils/Inspector.h" 


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
              ShaderManager& shaderManagerInstance, SceneManager& sceneManager,
              TextureManager& textureManager);  // Constructor
        void SetSceneManagerContext(SceneManager* sceneManager); // Set the SceneManager context for the UIManager
        void Render(); // Render the UIManager

    private:
        ScenePanel scenePanel; // Scene Panel
        Viewport& viewport; // Viewport
        DoodleManager& doodleManager; // Doodle Util
        PaletteManager& paletteManager;
        SceneManager& sceneManager; // SceneManager
        Inspector inspector; // Inspector
        CalculatorManager& calculatorManager;
    };
}

#endif // UI_MANAGER_H