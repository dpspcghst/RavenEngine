#ifndef RAVENENGINE_RENDERER_H
#define RAVENENGINE_RENDERER_H

#include <glad/glad.h> // handles OpenGL function pointers
#include <array> // std::array
#include <glm/glm.hpp> // glm::vec4
#include <glm/gtc/matrix_transform.hpp> // glm::ortho
#include "Primitives/Plane.h" // Include the Plane class

namespace RavenEngine {

class Renderer {
public:
    static const int RENDERER_WIDTH = 1280;
    static const int RENDERER_HEIGHT = 720;

    Renderer(int gameWidth = RENDERER_WIDTH, int gameHeight = RENDERER_HEIGHT); // Constructor
    ~Renderer(); // Destructor

    bool InitializeRenderer();
    void ShutdownRenderer();

    void StartFrame();
    void FinishFrame();

    float GetWidth() const { return static_cast<float>(gameWidth); }
    float GetHeight() const { return static_cast<float>(gameHeight); }

    void SetGLViewport(int x, int y, int width, int height);
    GLuint GetCurrentTexture();

    void SetProjectionMatrix(const glm::mat4& projection) { // Update this method to accept a glm::mat4 parameter
        projectionMatrix = projection;
    }

    void UpdateProjectionMatrix(); // Declare the UpdateProjection method

    const glm::mat4& GetProjectionMatrix() const {
        return projectionMatrix;
    }

private:
    int gameWidth, gameHeight; // Dimensions for rendering
    std::array<float, 4> screenClearColor; // Clear color
    GLuint framebufferObject; // Framebuffer object
    GLuint currentTexture; // Texture object

    Plane testPlane; // Test plane
    glm::mat4 projectionMatrix; // Projection matrix
};

} // namespace RavenEngine

#endif // RAVENENGINE_RENDERER_H