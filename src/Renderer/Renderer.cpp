#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Assets/Shaders/ShaderManager.h"

namespace RavenEngine {

Renderer::Renderer() 
    : screenWidth(800), screenHeight(600), framebuffer(0), texture(0) {
    std::cout << "Renderer constructor called" << std::endl;
}

Renderer::~Renderer() {
    std::cout << "Renderer destructor called" << std::endl;
    Shutdown(); // Ensure resources are cleaned up
}

bool Renderer::Initialize(int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }

    SetViewport(0, 0, screenWidth, screenHeight);

    // Set the default clear color
    clearColor = {0.149f, 0.137f, 0.788f, 1.0f};

    // Create a framebuffer object
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create a texture object
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screenWidth, screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Attach the texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void Renderer::Shutdown() {
    std::cout << "Shutting down Renderer" << std::endl;
    glDeleteFramebuffers(1, &framebuffer);
    glDeleteTextures(1, &texture);
}

void Renderer::BeginScene() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EndScene() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::Clear() {
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetViewport(int x, int y, int width, int height) {
    std::cout << "Setting viewport to: " << x << "," << y << " - " << width << "x" << height << std::endl;
    glViewport(x, y, width, height);
}

void Renderer::OnWindowResize(int newWidth, int newHeight) {
    screenWidth = newWidth;
    screenHeight = newHeight;
    SetViewport(0, 0, newWidth, newHeight);
}

GLuint Renderer::GetTexture() {
    return texture;
}

} // namespace RavenEngine
