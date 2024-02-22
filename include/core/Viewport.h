// viewport.h
// #####################
#ifndef RAVENENGINE_VIEWPORT_H
#define RAVENENGINE_VIEWPORT_H
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "imgui.h"

// Raven includes
#include "../../src/Renderer/Renderer.h"
#include "../../src/Scene/SceneNode.h"
#include "SettingsManager.h"
#include "GameLoop.h"

namespace RavenEngine {

class Viewport {
public:
    explicit Viewport(GLFWwindow* window);
    ~Viewport();

    void Render(SceneNode& rootNode);
    void DrawPlaybackBar();
    float CalculateZoom();
    ImVec2 CalculatePadding(const ImVec2& viewportPanelSize, float zoom);

private:
    GLFWwindow* window;
    Renderer renderer;
    GameLoop gameLoop;
    ImVec2 size;
    ImVec2 offset;
};

} // namespace RavenEngine

#endif // RAVENENGINE_VIEWPORT_H