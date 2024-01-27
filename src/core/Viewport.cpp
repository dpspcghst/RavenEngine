#include "../Renderer/Renderer.h"
#include "Viewport.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace RavenEngine {

Viewport::Viewport(GLFWwindow* win) 
        : window(win),
            renderer(SettingsManager::GetInstance()),
            size(ImVec2(static_cast<float>(renderer.GetSize().first), static_cast<float>(renderer.GetSize().second))),
            offset(0, 0) { 
        // std::cout << "Initializing Viewport..." << std::endl;
        renderer.InitializeRenderer();
}

Viewport::~Viewport() {
    renderer.ShutdownRenderer();
    //std::cout << "Viewport resources cleaned up successfully." << std::endl;
}

void Viewport::Render(SceneNode& rootNode) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    
    // Set the window background color
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 oldColor = style.Colors[ImGuiCol_WindowBg]; // Save the old color
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0094f, 0.0094f, 0.0094f, 1.0f);
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();


    // Check the state of the rootNode and its children
    //std::cout << "rootNode has " << rootNode.GetChildren().size() << " children" << std::endl;

    // Debugging information
    //std::cout << "Address of rootNode in Viewport: " << &rootNode << std::endl;

    renderer.StartFrame();
    renderer.RenderScene(rootNode);
    renderer.FinishFrame();

    GLuint textureId = renderer.GetCurrentTexture(); // Get the renderer's output texture ID

    // Calculate UV coordinates to maintain the renderer's aspect ratio within the viewport
    float uvX = 1.0f;
    float uvY = 1.0f;

    // Get the scroll wheel delta and adjust the zoom factor
    static float zoom = 1.0f;
    float targetZoom = zoom + io.MouseWheel * 0.1f;
    targetZoom = std::max(targetZoom, 0.1f); // Clamp the target zoom
    zoom = zoom + (targetZoom - zoom) * 0.1f; // Adjust the zoom smoothly

    // Calculate padding to center the renderer's output, taking into account the zoom factor
    float paddingX = (viewportPanelSize.x - renderer.GetWidth() * zoom) / 2.0f;
    float paddingY = (viewportPanelSize.y - renderer.GetHeight() * zoom) / 2.0f;
    paddingX = paddingX > 0 ? paddingX : 0;
    paddingY = paddingY > 0 ? paddingY : 0;

    // Set cursor position to apply padding
    ImGui::SetCursorPos(ImVec2(paddingX + offset.x, paddingY + offset.y));

    // Panning
    if (ImGui::IsWindowFocused()) {
        bool isPanning = io.MouseDown[ImGuiMouseButton_Middle];
        static ImVec2 initialMousePos;
        static ImVec2 initialOffset;

        if (isPanning) {
            if (!io.MouseDown[ImGuiMouseButton_Middle]) {
                // If the mouse button was just released, stop panning
                isPanning = false;
            } else if (!io.MouseDownDuration[ImGuiMouseButton_Middle]) {
                // If the mouse button was just pressed, start panning
                initialMousePos = io.MousePos;
                initialOffset = offset;
            } else {
                // If the mouse button is being held down, update the offset based on the mouse movement
                offset.x = initialOffset.x + (io.MousePos.x - initialMousePos.x) / zoom;
                offset.y = initialOffset.y + (io.MousePos.y - initialMousePos.y) / zoom;
            }
        }
    }

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