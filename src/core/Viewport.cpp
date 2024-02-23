// viewport.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes
// Raven includes
#include "../Renderer/Renderer.h"
#include "Viewport.h"
#include "../../include/utils/playbackbar.h"
#include "../../include/core/GameStateManager.h"

namespace RavenEngine {

Viewport::Viewport(GLFWwindow* win) 
        : window(win),
            renderer(SettingsManager::GetInstance()),
            size(ImVec2(static_cast<float>(renderer.GetSize().first), static_cast<float>(renderer.GetSize().second))),
            offset(0, 0) { 
        // std::cout << "Initializing Viewport..." << std::endl;
        renderer.InitializeRenderer();

        std::cout << "Viewport initialized successfully." << std::endl;
}

Viewport::~Viewport() {
    renderer.ShutdownRenderer();
    //std::cout << "Viewport resources cleaned up successfully." << std::endl;
}

void Viewport::Render(SceneNode& rootNode) {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{0, 0});
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 oldColor = style.Colors[ImGuiCol_WindowBg];
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0094f, 0.0094f, 0.0094f, 1.0f);

    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    // No need to check the game state here as rendering is now unconditional
    renderer.StartFrame();
    renderer.RenderScene(rootNode);
    renderer.FinishFrame();

    // Always perform these operations to ensure the texture is displayed
    float zoom = CalculateZoom();
    ImVec2 padding = CalculatePadding(viewportPanelSize, zoom);
    ImGui::SetCursorPos(padding);

    GLuint textureId = renderer.GetCurrentTexture();
    ImGui::Image(reinterpret_cast<void*>(static_cast<intptr_t>(textureId)),
                 ImVec2(renderer.GetWidth() * zoom, renderer.GetHeight() * zoom),
                 ImVec2(0, 0), ImVec2(1, 1));

    DrawPlaybackBar();

    ImGui::End();
    style.Colors[ImGuiCol_WindowBg] = oldColor;
    ImGui::PopStyleVar();
}


void Viewport::DrawPlaybackBar() {
    // Position and draw the playback bar at the bottom of the viewport
    ImGui::SetCursorPos(ImVec2(0, ImGui::GetWindowSize().y - ImGui::GetFrameHeightWithSpacing()));
    RavenEngine::PlaybackBar::Draw();
}

float Viewport::CalculateZoom() {
    // Implementation of zoom calculation based on user input
    static float zoom = 0.3f; // Initial zoom level
    float targetZoom = zoom + ImGui::GetIO().MouseWheel * 0.1f;
    return std::max(targetZoom, 0.1f); // Ensure zoom does not go below a minimum threshold
}

ImVec2 Viewport::CalculatePadding(const ImVec2& viewportPanelSize, float zoom) {
    // Calculate padding based on the current zoom level to center the image in the viewport
    float paddingX = (viewportPanelSize.x - renderer.GetWidth() * zoom) / 2.0f;
    float paddingY = (viewportPanelSize.y - renderer.GetHeight() * zoom) / 2.0f;
    return ImVec2(paddingX > 0 ? paddingX : 0, paddingY > 0 ? paddingY : 0);
}

} // namespace RavenEngine