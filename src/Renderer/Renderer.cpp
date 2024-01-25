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

Renderer::Renderer(SettingsManager& settingsManager)                                 // Constructor
        : gameWidth(settingsManager.GetResolutionWidth()),
            gameHeight(settingsManager.GetResolutionHeight()),
            fbManager(new FBManager(gameWidth, gameHeight)),
            shapeManager(){

        std::cout << "Renderer Constructor Ping" << std::endl;      
        std::cout << "Renderer created with size: " << gameWidth << "x" << gameHeight << std::endl; // Output 
}

Renderer::~Renderer() {                                                               // Destructor
    std::cout << "Renderer destructor called" << std::endl;
    delete fbManager;
}

// Initialize Renderer
bool Renderer::InitializeRenderer() {                                                 

    clearColor = {0.149f, 0.137f, 0.788f, 1.0f}; // Set the default clear color

    if (!fbManager->Initialize()) { // If the framebuffer fails to initialize
        std::cout << "Failed to initialize framebuffer" << std::endl; // Output
        return false; // Return false
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // if glad fails to load
        std::cout << "Failed to initialize GLAD" << std::endl; // output
        return false; // return false
    }

    SetGLViewport(0, 0, gameWidth, gameHeight); // Set the viewport to the game width and height
    // UpdateProjectionMatrix();                   // Update the projection matrix

    return true; // Return true if the renderer was initialized successfully
    //std::cout << "Renderer initialized successfully" << std::endl;
}

void Renderer::ShutdownRenderer() {
        // Implement the shutdown logic here, e.g., releasing resources
        std::cout << "Renderer shutdown" << std::endl;
}

void Renderer::SetGLViewport(int x, int y, int width, int height) {                   // Set GL viewport
    glViewport(x, y, width, height);
    gameWidth = width;
    gameHeight = height;
    //UpdateProjectionMatrix();
}

GLuint Renderer::GetCurrentTexture() {                                                // Get current texture
    return fbManager->GetCurrentTexture();
}

void Renderer::StartFrame() {
    // Bind the framebuffer and clear the screen
    glBindFramebuffer(GL_FRAMEBUFFER, fbManager->GetCurrentTexture());
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RenderScene(const SceneNode& rootNode) {
    // Traverse the scene graph and render each node
    for (const auto& child : rootNode.GetChildren()) {
        RenderNode(*child);
    }
}

void Renderer::FinishFrame() {                                                        // Finish frame
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::RenderNode(const RavenEngine::SceneNode& node) {
    // Get the shape associated with the node
    auto shape = node.GetShape();

    if (shape) {
        // Get the name of the shader associated with the shape
        std::string shaderName = shape->GetShaderName();

        // Use the shader by name
        RavenEngine::ShaderManager::GetInstance().UseShader(shaderName);

        // Set the transformation matrix uniform in the shader
        glm::mat4 transformMatrix = shape->GetTransformMatrix();
        RavenEngine::ShaderManager::GetInstance().SetMatrix4(shaderName, "transformMatrix", transformMatrix);

        // Render the shape
        shape->Render();
    }

    // Traverse the scene graph and render each child node
    for (const auto& child : node.GetChildren()) {
        RenderNode(*child);
    }
}


std::pair<int, int> Renderer::GetSize() const {                                       // Get size
    return std::make_pair(gameWidth, gameHeight);
}

} // namespace RavenEngine