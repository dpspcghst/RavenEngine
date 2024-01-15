#include "../include/Renderer/Renderer.h"
#include "Viewport.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace RavenEngine {

Viewport::Viewport(GLFWwindow* win) 
        : window(win), 
            size(ImVec2(Renderer::RENDERER_WIDTH, Renderer::RENDERER_HEIGHT)), 
            renderer(Renderer::RENDERER_WIDTH, Renderer::RENDERER_HEIGHT) { 
        std::cout << "Initializing Viewport..." << std::endl;
        renderer.InitializeRenderer();
        std::cout << "Viewport initialized successfully." << std::endl;
}

Viewport::~Viewport() {
    renderer.ShutdownRenderer();
    std::cout << "Viewport resources cleaned up successfully." << std::endl;
}

void Viewport::Render() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    
    // Set the window background color
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 oldColor = style.Colors[ImGuiCol_WindowBg]; // Save the old color
    style.Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); // Set the background color to red

    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    renderer.StartFrame();  // Start the renderer's frame
    // ... Renderer render code ...
    renderer.FinishFrame(); // Finish the renderer's frame

    GLuint textureId = renderer.GetCurrentTexture(); // Get the renderer's output texture ID

    // Calculate UV coordinates to maintain the renderer's aspect ratio within the viewport
    float uvX = 1.0f;
    float uvY = 1.0f;

    // Get the scroll wheel delta and adjust the zoom factor
    static float zoom = 1.0f;
    float targetZoom = zoom + ImGui::GetIO().MouseWheel * 0.1f;
    targetZoom = std::max(targetZoom, 0.1f); // Clamp the target zoom
    zoom = zoom + (targetZoom - zoom) * 0.1f; // Adjust the zoom smoothly

    // Calculate padding to center the renderer's output, taking into account the zoom factor
    float paddingX = (viewportPanelSize.x - renderer.GetWidth() * zoom) / 2.0f;
    float paddingY = (viewportPanelSize.y - renderer.GetHeight() * zoom) / 2.0f;
    paddingX = paddingX > 0 ? paddingX : 0;
    paddingY = paddingY > 0 ? paddingY : 0;

    // Set cursor position to apply padding
    ImGui::SetCursorPos(ImVec2(paddingX, paddingY));

    // Render the texture to the viewport with zoom
    ImGui::Image(
        reinterpret_cast<void*>(static_cast<intptr_t>(textureId)),
        ImVec2(renderer.GetWidth() * zoom, renderer.GetHeight() * zoom), // Use renderer's size for the image, adjusted by the zoom factor
        ImVec2(0, 0), // UV start coordinates
        ImVec2(uvX, uvY) // UV end coordinates, adjusted to match the renderer's size
    );

    ImGui::End();

    // Reset the window background color
    style.Colors[ImGuiCol_WindowBg] = oldColor;

    ImGui::PopStyleVar();
}

} // namespace RavenEngine


