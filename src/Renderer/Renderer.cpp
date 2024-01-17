#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Assets/Shaders/ShaderManager.h"
#include "../../include/Scene/SceneManager.h"

namespace RavenEngine {

Renderer::Renderer(SettingsManager& settingsManager)
    : gameWidth(settingsManager.GetResolutionWidth()), 
      gameHeight(settingsManager.GetResolutionHeight()), 
      framebufferObject(0), 
      currentTexture(0) {
    std::cout << "Renderer created with size: " << gameWidth << "x" << gameHeight << std::endl;
}

Renderer::~Renderer() {
    std::cout << "Renderer destructor called" << std::endl;
    ShutdownRenderer();
}

bool Renderer::InitializeRenderer() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }

    // Initialize the ShaderManager and load your shaders
    shaderManager.LoadShader("default", "../../Assets/Shaders/PointVertexShader.glsl", "../../Assets/Shaders/PointFragmentShader.glsl");

    SetGLViewport(0, 0, gameWidth, gameHeight);

    glGenFramebuffers(1, &framebufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);

    glGenTextures(1, &currentTexture);
    glBindTexture(GL_TEXTURE_2D, currentTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, gameWidth, gameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, currentTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        return false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}

void Renderer::ShutdownRenderer() {
    std::cout << "Shutting down Renderer" << std::endl;
    glDeleteFramebuffers(1, &framebufferObject);
    glDeleteTextures(1, &currentTexture);
}

// Updated StartFrame method without SceneManager parameter
void Renderer::StartFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);
    glClearColor(SCREEN_CLEAR_COLOR[0], SCREEN_CLEAR_COLOR[1], SCREEN_CLEAR_COLOR[2], SCREEN_CLEAR_COLOR[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::FinishFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::SetGLViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
    gameWidth = width;
    gameHeight = height;
}

GLuint Renderer::GetCurrentTexture() {
    return currentTexture;
}

void Renderer::RenderNode(const SceneNode& node) {
    shaderManager.UseShader(node.GetName());
    // Set uniforms, bind VAO, etc.
    // Draw call (glDrawArrays or glDrawElements)
}

// void Renderer::RenderScene(const SceneManager& sceneManager) {
//     for (const auto& node : sceneManager.GetNodes()) {
//     RenderNode(*node);
//     }
// }

} // namespace RavenEngine