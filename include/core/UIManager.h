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
#include "../utils/Doodle/DoodleManager.h"

namespace RavenEngine {
    // Forward declarations
    class ScenePanel;
    class SceneManager;
    class DoodleManager;

    class UIManager {
    public:
        UIManager(DoodleManager& doodleManager, Viewport& viewport, ShaderManager& shaderManagerInstance, SceneManager& sceneManager); // Constructor
        void SetSceneManagerContext(SceneManager* sceneManager); // Set the SceneManager context for the UIManager (i dont really know what this does)
        void Render(); // Render the UIManager

    private:
        ScenePanel scenePanel; // Scene Panel
        Viewport& viewport; // Viewport
        DoodleManager& doodleManager; // Doodle Util
        SceneManager& sceneManager; // SceneManager
    };
}

#endif // UI_MANAGER_H