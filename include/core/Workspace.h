#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <GLFW/glfw3.h>
#include "UIManager.h"
#include "Viewport.h" // Include the Viewport class
#include "../Scene/SceneManager.h"
#include "ComponentManager.h"

using RavenEngine::SceneManager;

class Workspace {
public:
    Workspace(GLFWwindow* mainWin);
    void Render();
    void AddComponent(const std::string& componentName);
    void Update();

private:
    GLFWwindow* window;
    UIManager uiManager;
    RavenEngine::Viewport viewport; // Add a Viewport as a member variable
    SceneManager sceneManager;
    ComponentManager componentManager;
};

#endif // WORKSPACE_H