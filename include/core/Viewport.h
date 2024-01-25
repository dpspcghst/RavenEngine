#ifndef RAVENENGINE_VIEWPORT_H
#define RAVENENGINE_VIEWPORT_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "../../src/Renderer/Renderer.h"
#include "../../src/Scene/SceneNode.h"  // Include the SceneNode header
#include "SettingsManager.h"

namespace RavenEngine {

class Viewport {
public:
    explicit Viewport(GLFWwindow* window);
    ~Viewport();
    void Render(SceneNode& rootNode);

private:
    GLFWwindow* window;
    Renderer renderer;
    ImVec2 size;
    ImVec2 offset;
};

} // namespace RavenEngine

#endif // RAVENENGINE_VIEWPORT_H