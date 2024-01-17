#ifndef RAVENENGINE_VIEWPORT_H
#define RAVENENGINE_VIEWPORT_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "Renderer/Renderer.h"
#include "SettingsManager.h"

namespace RavenEngine {

class Viewport {
public:
    Viewport(GLFWwindow* window, SettingsManager& settingsManager); // Add SettingsManager to the constructor
    ~Viewport();
    void Render();

private:
    GLFWwindow* window;
    Renderer renderer;
    ImVec2 size; // Size of the viewport
};

} // namespace RavenEngine

#endif // RAVENENGINE_VIEWPORT_H