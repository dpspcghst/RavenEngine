#include "../include/Renderer/Renderer.h"
#include "Viewport.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace RavenEngine {

Viewport::Viewport(GLFWwindow* win) : window(win), size(ImVec2(800, 600)) {
    std::cout << "Initializing Viewport..." << std::endl;

    // Initialize Renderer
    renderer.Initialize(static_cast<int>(size.x), static_cast<int>(size.y));

    std::cout << "Viewport initialized successfully." << std::endl;
}

Viewport::~Viewport() {
    renderer.Shutdown();

    std::cout << "Viewport resources cleaned up successfully." << std::endl;
}

void Viewport::Render() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});

    // Set the default size and position for the viewport window
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(600, 50), ImGuiCond_FirstUseEver);

    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    // Switch to your own OpenGL context
    glfwMakeContextCurrent(window);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    if (viewportPanelSize.x != size.x || viewportPanelSize.y != size.y) {
        renderer.OnWindowResize(static_cast<int>(viewportPanelSize.x), static_cast<int>(viewportPanelSize.y));
        size.x = viewportPanelSize.x;
        size.y = viewportPanelSize.y;
    }

    renderer.Clear(); // Clear the screen before rendering
    renderer.BeginScene();

    renderer.EndScene();

    // Switch back to ImGui's OpenGL context
    glfwMakeContextCurrent(static_cast<GLFWwindow*>(ImGui::GetMainViewport()->PlatformHandle));

    // Get the texture from your OpenGL rendering
    GLuint textureId = renderer.GetTexture();

    // Display the texture in the ImGui window
    ImGui::Image((void*)(intptr_t)textureId, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
    ImGui::PopStyleVar();
}

void Viewport::Resize(int newWidth, int newHeight) {
    renderer.OnWindowResize(newWidth, newHeight);
}

} // namespace RavenEngine