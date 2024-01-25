#ifndef RAVENENGINE_RENDERER_H
#define RAVENENGINE_RENDERER_H

#include <glad/glad.h>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SettingsManager.h"
#include "../../Assets/Shaders/ShaderManager.h"
#include "Shapes/ShapeManager.h"
#include "FBO/FBManager.h"

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

    void RenderNode(const SceneNode& node);
    // void UpdateProjectionMatrix();

    std::pair<int, int> GetSize() const;

    void SetCameraPosition(const glm::vec2& position);

private:
    int gameWidth, gameHeight;
    std::array<float, 4> clearColor;
    glm::mat4 projectionMatrix;

    glm::vec2 cameraPosition;
    glm::mat4 viewMatrix;

    ShapeManager shapeManager;
    FBManager* fbManager; // Add a pointer to the FBManager
};

} // namespace RavenEngine

#endif // RAVENENGINE_RENDERER_H