#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include "Console.h"
#include "../Scene/SceneHierarchyPanel.h"
#include "../Scene/SceneManager.h"
#include "Viewport.h"
#include "../utils/Doodle/DoodleManager.h"

namespace RavenEngine {
    class Console;
    class SceneHierarchyPanel;
    class SceneManager;
    class DoodleManager;

    class UIManager {
    public:
        UIManager(Viewport& viewport, DoodleManager& doodleManager);
        void SetSceneManagerContext(SceneManager* sceneManager);
        void Render();
        void AddLogToConsole(const std::string& message);

    private:
        Console console;
        SceneHierarchyPanel sceneHierarchyPanel;
        Viewport& viewport;
        DoodleManager& doodleManager; // Member variable
    };
}

#endif // UI_MANAGER_H