// renderer.h
// #####################
#ifndef RAVENENGINE_RENDERER_H
#define RAVENENGINE_RENDERER_H
// #####################
// #include section
// #####################
// Standard library includes
#include <array>
#include <vector>
#include <memory>

// Third party includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Raven includes
#include "SettingsManager.h"
#include "Shaders/ShaderManager.h"
#include "FBO/FBManager.h"
#include "Camera/Camera.h"
#include "Shapes/Shape.h"
#include "../Scene/SceneGraphRenderer.h"

namespace RavenEngine {

class SceneNode; // Forward declaration of SceneNode

class Renderer {
public:
    Renderer(SettingsManager& settingsManager);
    ~Renderer();

    bool InitializeRenderer();
    void ShutdownRenderer();

    float GetWidth() const { return static_cast<float>(gameWidth); }
    float GetHeight() const { return static_cast<float>(gameHeight); }

    void StartFrame();
    void RenderScene(const SceneNode& node); // Changed to take a reference to SceneNode
    void FinishFrame();

    void SetGLViewport(int x, int y, int width, int height);
    GLuint GetCurrentTexture();

    void RenderNode(const SceneNode& node, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    std::pair<int, int> GetSize() const;

    void RenderPausedScreen();

private:
    std::unique_ptr<SceneGraphRenderer> sceneGraphRenderer; // Add a unique pointer to the SceneGraphRenderer

    int gameWidth, gameHeight;  // aspect ratio set by the settings manager
    std::array<float, 4> clearColor;
    
    FBManager* fbManager; // Add a pointer to the FBManager

    std::unique_ptr<Camera> camera; // Add a Camera member variable

    std::vector<std::shared_ptr<Shape>> shapes; // A unified vector to hold all Shape objects
    float pauseTimer = 0.0f;
    void UpdateColors(); // Declare the UpdateColors method


    
};

} // namespace RavenEngine

#endif // RAVENENGINE_RENDERER_H
