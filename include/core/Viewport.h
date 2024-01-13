#ifndef RAVENENGINE_VIEWPORT_H
#define RAVENENGINE_VIEWPORT_H

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"
#include "Renderer/Renderer.h"

namespace RavenEngine {

class Viewport {
public:
    Viewport(GLFWwindow* window);
    ~Viewport(); // Declare the destructor
    void Render();
    void Resize(int width, int height);

private:
    GLFWwindow* window;
    ImVec2 size; // Size of the viewport
    Renderer renderer;
};

} // namespace RavenEngine

#endif // RAVENENGINE_VIEWPORT_H