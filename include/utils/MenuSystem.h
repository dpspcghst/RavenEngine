#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <GLFW/glfw3.h>
#include <string>
#include "Doodle/DoodleManager.h"
#include "UIManager.h" // Include UIManager

namespace RavenEngine {

class Workspace; // Forward declaration

class MenuSystem {
private:
    Workspace& workspace;
    GLFWwindow* mainWindow;
    bool fileDialogOpen = false; // State variable to track file dialog status
    DoodleManager& doodleManager;
    UIManager& uiManager; // Add this line

public:
    MenuSystem(Workspace& workspace, GLFWwindow* window, DoodleManager& doodleManager, UIManager& uiManager); // Update this line
    void createMainMenu();
    void createFileMenu();
    void createToolsMenu();
    void handleFileMenuItems();
    void handleToolsMenuItems();
    void handleFileDialog();
};

} // namespace RavenEngine

#endif // MENU_SYSTEM_H