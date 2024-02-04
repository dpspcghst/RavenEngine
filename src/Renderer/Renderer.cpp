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

        // Print the orthographic projection boundaries
        // std::cout << "Orthographic projection boundaries:" << std::endl;
        // std::cout << "Left: " << left << ", Right: " << right << std::endl;
        // std::cout << "Bottom: " << bottom << ", Top: " << top << std::endl;
        // std::cout << "Near: " << nearPlane << ", Far: " << farPlane << std::endl;
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
        //std::cout << "Failed to initialize framebuffer" << std::endl; // Output
        return false; // Return false
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { // if glad fails to load
        //std::cout << "Failed to initialize GLAD" << std::endl; // output
        return false; // return false
    }
    
    return true; // Return true if the renderer was initialized successfully
    std::cout << "Renderer initialized successfully" << std::endl;
}

void Renderer::ShutdownRenderer() {
        // Implement the shutdown logic here, e.g., releasing resources
        //std::cout << "Renderer shutdown" << std::endl;
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
        ShaderManager::GetInstance().UpdateUniformBuffer(uboName, &props, sizeof(props));
    }
}

void Renderer::RenderScene(const SceneNode& rootNode) {
    UpdateColors(); // Update the colors of all shapes
    auto viewMatrix = camera->GetViewMatrix();
    auto projectionMatrix = camera->GetProjectionMatrix();

    // Render each node with updated matrices
    if (!rootNode.GetChildren().empty()) {
        for (const auto& child : rootNode.GetChildren()) {
            RenderNode(*child, viewMatrix, projectionMatrix);
        }
    }
}

void Renderer::FinishFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::RenderNode(const SceneNode& node, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    const GLuint FIXED_BINDING_POINT = 0;
    auto shape = node.GetShape();
    if (!shape) {
        std::cerr << "RENDERER::RENDERNODE Shape is NULL for the node: " << node.GetName() << std::endl;
        return;
    }

    std::string shaderName = shape->GetShaderName();
    ShaderManager& shaderManager = ShaderManager::GetInstance();

    if (!shaderManager.IsShaderLoaded(shaderName)) {
        std::cerr << "RENDERER::RENDERNODE Shader " << shaderName << " is not loaded.\n";
        return;
    }

    GLuint shaderProgram = shaderManager.GetShader(shaderName);
    if (shaderProgram == 0 || !glIsProgram(shaderProgram)) {
        std::cerr << "RENDERER::RENDERNODE Invalid shader program ID for shader: " << shaderName << std::endl;
        return;
    }
    glUseProgram(shaderProgram);
    std::cout << "Shader " << shaderName << " with program ID " << shaderProgram << " is now bound." << std::endl;

    // Set the transformation matrices
    glm::mat4 modelMatrix = shape->GetTransformMatrix();
    shaderManager.SetMatrix4(shaderName, "model", modelMatrix);
    shaderManager.SetMatrix4(shaderName, "view", viewMatrix);
    shaderManager.SetMatrix4(shaderName, "projection", projectionMatrix);

    // Bind UBO for the current shape
    std::string uboName = shape->GetMaterialUBOName();
    UniformBufferProperties uboProps = shaderManager.GetUBOProperties(uboName);
    if (uboProps.bufferID == 0) {
        std::cerr << "RENDERER::RENDERNODE UBO " << uboName << " not found for shape: " << node.GetName() << std::endl;
        return;
    }

    // Obtain the block index for the UBO in the shader
    GLuint blockIndex = glGetUniformBlockIndex(shaderProgram, "MaterialProperties");
    if (blockIndex == GL_INVALID_INDEX) {
        std::cerr << "RENDERER::RENDERNODE Uniform block 'MaterialProperties' not found in shader program: " << shaderProgram << std::endl;
        return;
    }

    // Bind the UBO to a fixed binding point
    glUniformBlockBinding(shaderProgram, blockIndex, FIXED_BINDING_POINT);
    glBindBufferBase(GL_UNIFORM_BUFFER, FIXED_BINDING_POINT, uboProps.bufferID);

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after binding UBO: " << error << std::endl;
    }

    // Render the shape
    shape->Render(viewMatrix, projectionMatrix);

    error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after rendering shape: " << error << std::endl;
    }

    std::cout << "Shader " << shaderName << " with program ID " << shaderProgram << " is now unbound." << std::endl;
    // Render children nodes recursively
    for (const auto& child : node.GetChildren()) {
        RenderNode(*child, viewMatrix, projectionMatrix);
    }
}


std::pair<int, int> Renderer::GetSize() const {                                       // Get size
    return std::make_pair(gameWidth, gameHeight);
}

} // namespace RavenEngine