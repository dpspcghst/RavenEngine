// render.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third party includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h> // Include glad first
#include <GLFW/glfw3.h> // Then include GLFW

// Raven includes
#include "Renderer.h"
#include "FBO/FBManager.h"
#include "../../Assets/Shaders/ShaderManager.h"
#include "../../src/Scene/SceneManager.h"

namespace RavenEngine {

Renderer::Renderer(SettingsManager& settingsManager)
        : gameWidth(settingsManager.GetResolutionWidth()),
            gameHeight(settingsManager.GetResolutionHeight()),
            fbManager(new FBManager(gameWidth, gameHeight)),
            shapeManager(), testTriangle() {

        // Initialize camera for 2D orthographic projection
        float left = 0.0f, right = static_cast<float>(gameWidth); // Stretch the right boundary
        float bottom = 0.0f, top = static_cast<float>(gameHeight); // Stretch the top boundary
        float nearPlane = -1.0f, farPlane = 1.0f;
        camera = std::make_unique<Camera>(left, right, bottom, top, nearPlane, farPlane);
}

Renderer::~Renderer() {                                                               // Destructor
    std::cout << "Renderer destructor called" << std::endl;
    delete fbManager;
}

// Initialize Renderer
bool Renderer::InitializeRenderer() {


    clearColor = {0.149f, 0.137f, 0.788f, 1.0f}; // Set the default clear color
    SetGLViewport(0, 0, gameWidth, gameHeight); // Set the viewport to the game width and height

    if (!fbManager->Initialize()) { // If the framebuffer fails to initialize
        std::cout << "Failed to initialize framebuffer" << std::endl; // Output
        return false; // Return false
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // if glad fails to load
        std::cout << "Failed to initialize GLAD" << std::endl; // output
        return false; // return false
    }
    
    return true; // Return true if the renderer was initialized successfully
    std::cout << "Renderer initialized successfully" << std::endl;
}

void Renderer::ShutdownRenderer() {
        // Implement the shutdown logic here, e.g., releasing resources
        std::cout << "Renderer shutdown" << std::endl;
}

void Renderer::SetGLViewport(int x, int y, int width, int height) {                   // Set GL viewport
    glViewport(x, y, width, height);
    gameWidth = width;
    gameHeight = height;
}

GLuint Renderer::GetCurrentTexture() {                                                // Get current texture
    return fbManager->GetCurrentTexture();
}

void Renderer::StartFrame() {
    // Bind the framebuffer and clear the screen
    glBindFramebuffer(GL_FRAMEBUFFER, fbManager->GetCurrentTexture());
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
}

void Renderer::RenderScene(const SceneNode& rootNode) {

    auto viewMatrix = camera->GetViewMatrix();
    auto projectionMatrix = camera->GetProjectionMatrix();

    // cout view/projection matrices
    std::cout << "viewMatrix: " << glm::to_string(viewMatrix) << std::endl;
    std::cout << "projectionMatrix: " << glm::to_string(projectionMatrix) << std::endl;

    // Render each node with updated matrices
    if (!rootNode.GetChildren().empty()) {
        for (const auto& child : rootNode.GetChildren()) {
            RenderNode(*child, viewMatrix, projectionMatrix);
        }
    }
}

void Renderer::FinishFrame() {                                                        // Finish frame
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::RenderNode(const SceneNode& node, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    auto shape = node.GetShape();
    std::cout << "shape: " << shape << std::endl;

    if (shape) {
        std::string shaderName = shape->GetShaderName();
        if (!shaderName.empty()) {
            ShaderManager::GetInstance().UseShader(shaderName);
            ShaderManager::GetInstance().SetMatrix4(shaderName, "model", shape->GetTransformMatrix());
            ShaderManager::GetInstance().SetMatrix4(shaderName, "view", viewMatrix);
            ShaderManager::GetInstance().SetMatrix4(shaderName, "projection", projectionMatrix);
            shape->Render(viewMatrix, projectionMatrix);
        }
    }

    // Render children
    for (const auto& child : node.GetChildren()) {
        RenderNode(*child, viewMatrix, projectionMatrix);
    }
}

std::pair<int, int> Renderer::GetSize() const {                                       // Get size
    return std::make_pair(gameWidth, gameHeight);
}

} // namespace RavenEngine