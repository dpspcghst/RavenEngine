#ifndef RAVENENGINE_RENDERER_H
#define RAVENENGINE_RENDERER_H

#include <glad/glad.h>
#include <array>
#include "SettingsManager.h"
#include "../../Assets/Shaders/ShaderManager.h"

// Forward declarations
namespace RavenEngine {
    class SceneNode; // Forward declaration of SceneNode
}

namespace RavenEngine {

class Renderer {
public:
    // Constructor and Destructor
    Renderer(SettingsManager& settingsManager);
    ~Renderer();

    // Initialize and shutdown methods
    bool InitializeRenderer();
    void ShutdownRenderer();

    // Getters for game dimensions
    float GetWidth() const { return static_cast<float>(gameWidth); }
    float GetHeight() const { return static_cast<float>(gameHeight); }

    // Render methods
    void StartFrame();  // Updated signature: No longer requires SceneManager
    void FinishFrame();

    // GL viewport and texture methods
    void SetGLViewport(int x, int y, int width, int height);
    GLuint GetCurrentTexture();

    // Define screenClearColor as a static constant
    static constexpr std::array<float, 4> SCREEN_CLEAR_COLOR = {0.149f, 0.137f, 0.788f, 1.0f};

    void RenderNode(const SceneNode& node);
    //void RenderScene(const SceneNode& node); // This method can remain as is, assuming SceneManager is used here

private:
    // Private member variables
    int gameWidth, gameHeight;
    GLuint framebufferObject;
    GLuint currentTexture;
    ShaderManager shaderManager;
};

} // End of RavenEngine namespace

#endif // RAVENENGINE_RENDERER_H
