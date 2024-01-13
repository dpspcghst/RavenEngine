#ifndef RAVENENGINE_RENDERER_H
#define RAVENENGINE_RENDERER_H

#include <glad/glad.h>
#include <array>
#include <glm/glm.hpp>

namespace RavenEngine {

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool Initialize(int screenWidth, int screenHeight);
    void Shutdown();

    void BeginScene();
    void EndScene();

    void Clear();
    void SetViewport(int x, int y, int width, int height);
    void OnWindowResize(int newWidth, int newHeight);

    GLuint GetTexture(); // Method to get the texture ID

private:
    int screenWidth, screenHeight;
    std::array<float, 4> clearColor;
    GLuint framebuffer; // Framebuffer object
    GLuint texture; // Texture object
};

} // namespace RavenEngine

#endif // RAVENENGINE_RENDERER_H
