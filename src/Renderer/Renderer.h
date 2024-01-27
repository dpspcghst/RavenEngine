#ifndef RAVENENGINE_RENDERER_H
#define RAVENENGINE_RENDERER_H

// #include section
// #####################
// Standard library includes
#include <array>

// Third party includes
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Raven includes
#include "SettingsManager.h"
#include "../../Assets/Shaders/ShaderManager.h"
#include "Shapes/ShapeManager.h"
#include "FBO/FBManager.h"
#include "Camera.h"

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

    static constexpr std::array<float, 4> SCREEN_CLEAR_COLOR = {0.149f, 0.137f, 0.788f, 1.0f};

    void RenderNode(const SceneNode& node, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix); // Updated signature

    std::pair<int, int> GetSize() const;

private:
    int gameWidth, gameHeight;
    std::array<float, 4> clearColor;

    ShapeManager shapeManager;
    FBManager* fbManager; // Add a pointer to the FBManager

    Shape2D* testTriangle; // Add a pointer to a Shape2D

    std::unique_ptr<Camera> camera; // Add a Camera member variable
};

} // namespace RavenEngine

#endif // RAVENENGINE_RENDERER_H
