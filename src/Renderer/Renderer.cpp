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
#include "UBO/UniformBuffer.h"
#include "Materials/MaterialProperties.h"
#include "Materials/MaterialProperties3D.h"
#include "Shaders/ShaderManager.h"
#include "../../src/Scene/SceneManager.h"

namespace RavenEngine {

Renderer::Renderer(SettingsManager& settingsManager)
        : gameWidth(settingsManager.GetResolutionWidth()),
            gameHeight(settingsManager.GetResolutionHeight()),
            fbManager(new FBManager(gameWidth, gameHeight))
            {

        // Initialize camera for 2D orthographic projection
        float left = 0.0f, right = static_cast<float>(gameWidth); // Stretch the right boundary
        float bottom = 0.0f, top = static_cast<float>(gameHeight); // Stretch the top boundary
        float nearPlane = -1.0f, farPlane = 1.0f;
        camera = std::make_unique<Camera>(left, right, bottom, top, nearPlane, farPlane);

}

Renderer::~Renderer() {                                                               // Destructor
    //std::cout << "Renderer destructor called" << std::endl;
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
}

void Renderer::ShutdownRenderer() {
        // Implement the shutdown logic here, e.g., releasing resources
        //std::cout << "Renderer shutdown" << std::endl;
}

std::pair<int, int> Renderer::GetSize() const {                                       // Get size
    return std::make_pair(gameWidth, gameHeight);
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

void Renderer::UpdateColors() {
    // Iterate over all Shape2D objects and update their color
    for (auto& shape : shapes) {
        std::string uboName = shape->GetMaterialUBOName();
        MaterialProperties props;
        props.color = shape->GetColor();
        UniformBufferManager::GetInstance().UpdateUniformBuffer(uboName, &props, sizeof(props));
    }
}

void Renderer::RenderScene(const SceneNode& rootNode) {
    UpdateColors(); // Update the colors of all shapes
    auto viewMatrix = camera->GetViewMatrix();
    auto projectionMatrix = camera->GetProjectionMatrix();

    // Render each node with updated matrices
    if (!rootNode.GetChildren().empty()) { // If the root node has children
        for (const auto& child : rootNode.GetChildren()) {
            RenderNode(*child, viewMatrix, projectionMatrix);
            //std::cout << "RENDERER::RENDERSCENE Rendered node: " << child->GetName() << std::endl;
        }
    }
}

void Renderer::FinishFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::RenderNode(const SceneNode& node, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    auto shape = node.GetShape();
    if (!shape) {
        std::cerr << "RENDERER::RENDERNODE Shape is NULL for the node: " << node.GetName() << std::endl;
        return;
    }

    std::string shaderName = shape->GetShaderName();
    auto shaderProgramPtr = ShaderManager::GetInstance().GetShader(shaderName);
    if (!shaderProgramPtr) {
        std::cerr << "RENDERER::RENDERNODE Failed to retrieve shader program for '" << shaderName << "'" << std::endl;
        return;
    }

    shaderProgramPtr->Use();

    glm::mat4 modelMatrix = shape->GetTransformMatrix();
    shaderProgramPtr->SetUniform("model", modelMatrix);
    shaderProgramPtr->SetUniform("view", viewMatrix);
    shaderProgramPtr->SetUniform("projection", projectionMatrix);

    std::string uboName = shape->GetMaterialUBOName();
    auto uboProps = UniformBufferManager::GetInstance().GetUBOProperties(uboName);
    if (uboProps.bufferID != 0) {
        GLuint blockIndex = shaderProgramPtr->GetUniformBlockIndex("MaterialProperties");
        if (blockIndex != GL_INVALID_INDEX) {
            // Bind the UBO to a common binding point, e.g., 0
            glUniformBlockBinding(shaderProgramPtr->GetID(), blockIndex, 0);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboProps.bufferID);

            // Before drawing the shape, update its material properties in the UBO
            MaterialProperties props = {shape->GetColor()};
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(MaterialProperties), &props);

            std::cout << "RENDERER::RENDERNODE Updated UBO '" << uboName << "' for node: " << node.GetName() << std::endl;
        } else {
            std::cerr << "RENDERER::RENDERNODE 'MaterialProperties' uniform block not found in shader: " << shaderName << std::endl;
        }
    } else {
        std::cerr << "RENDERER::RENDERNODE Failed to find UBO: " << uboName << " in UniformBufferManager." << std::endl;
    }

    shape->Render(viewMatrix, projectionMatrix);

    for (const auto& child : node.GetChildren()) {
        RenderNode(*child, viewMatrix, projectionMatrix);
    }
}


} // namespace RavenEngine