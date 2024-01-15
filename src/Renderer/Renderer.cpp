#include "Renderer.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"
#include "../../Assets/Shaders/ShaderManager.h"

namespace RavenEngine {

Renderer::Renderer(int gameWidth, int gameHeight)
    : gameWidth(gameWidth), gameHeight(gameHeight), framebufferObject(0), currentTexture(0), testPlane() {
    screenClearColor = {0.149f, 0.137f, 0.788f, 1.0f}; // Set your favorite blue color
    UpdateProjectionMatrix(); // Correctly setup the projection matrix
    std::cout << "Renderer created with size: " << gameWidth << "x" << gameHeight << std::endl;
}

void Renderer::UpdateProjectionMatrix() {
    // Calculate the aspect ratio of the game's render target.
    float aspectRatio = static_cast<float>(gameWidth) / static_cast<float>(gameHeight);
    
    // Define the orthographic projection dimensions.
    // The larger dimension (width or height) will range from -1 to 1 in NDC space,
    // and the other dimension will be scaled according to the aspect ratio.
    float orthoWidth, orthoHeight;
    if (aspectRatio >= 1.0f) { // Wide aspect
        orthoWidth = aspectRatio;
        orthoHeight = 1.0f;
    } else { // Tall aspect
        orthoWidth = 1.0f;
        orthoHeight = 1.0f / aspectRatio;
    }
    // Use the calculated dimensions to set up an orthographic projection.
    projectionMatrix = glm::ortho(-orthoWidth, orthoWidth, -orthoHeight, orthoHeight, -1.0f, 1.0f);
}

Renderer::~Renderer() {
    std::cout << "Renderer destructor called" << std::endl;
    ShutdownRenderer();
}

bool Renderer::InitializeRenderer() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return false;
    }

    testPlane.Create();

    SetGLViewport(0, 0, gameWidth, gameHeight);
    //SetProjectionMatrix(glm::mat4(1.0f));

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

void Renderer::StartFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);
    glClearColor(screenClearColor[0], screenClearColor[1], screenClearColor[2], screenClearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 viewMatrix = glm::mat4(1.0f); // Create a default view matrix if you don't have one
    testPlane.Render();
}

void Renderer::FinishFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::SetGLViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
    gameWidth = width;
    gameHeight = height;
    UpdateProjectionMatrix(); // Update the projection matrix on viewport size change
}

GLuint Renderer::GetCurrentTexture() {
    return currentTexture;
}

} // namespace RavenEngine
