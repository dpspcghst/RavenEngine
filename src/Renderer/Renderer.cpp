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
#include "../Scene/SceneManager.h"
#include "../Scene/SceneGraphRenderer.h"
#include "Texture/TextureManager.h"

namespace RavenEngine {

Renderer::Renderer(SettingsManager& settingsManager)
        : gameWidth(settingsManager.GetResolutionWidth()),
            gameHeight(settingsManager.GetResolutionHeight()),
            fbManager(new FBManager(gameWidth, gameHeight)){

                // Initialize camera for 2D orthographic projection
                float left = 0.0f, right = static_cast<float>(gameWidth); // Stretch the right boundary
                float bottom = 0.0f, top = static_cast<float>(gameHeight); // Stretch the top boundary
                float nearPlane = -1.0f, farPlane = 1.0f;
                camera = std::make_unique<Camera>(left, right, bottom, top, nearPlane, farPlane);

                std::shared_ptr<RavenEngine::Camera> sharedCamera = std::move(camera);
                sceneGraphRenderer = std::make_unique<RavenEngine::SceneGraphRenderer>(sharedCamera);
}

Renderer::~Renderer() {                                                               // Destructor
    //std::cout << "Renderer destructor called" << std::endl;
    delete fbManager;
}

// Initialize Renderer
bool Renderer::InitializeRenderer() {                                                 // Initialize renderer

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

void Renderer::ShutdownRenderer() {                                                   // Shutdown renderer
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

void Renderer::StartFrame() {                                                         // Start frame
    // Bind the framebuffer and clear the screen
    glBindFramebuffer(GL_FRAMEBUFFER, fbManager->GetCurrentTexture());
    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
}

void Renderer::UpdateColors() {                                                       // Update colors
    // Iterate over all Shape objects and update their color
    for (auto& shape : shapes) {
        std::string uboName = shape->GetMaterialUBOName();
        if (shape->GetType() == RavenEngine::Shape::ShapeType::Shape2D) {
            MaterialProperties props;
            props.color = shape->GetColor();
            UniformBufferManager::GetInstance().UpdateUniformBuffer(uboName, &props, sizeof(props));
        } else if (shape->GetType() == RavenEngine::Shape::ShapeType::Shape3D) {
            MaterialProperties3D props;
            props.ambient = shape->GetAmbient();
            props.diffuse = shape->GetDiffuse();
            props.specular = shape->GetSpecular();
            props.shininess = shape->GetShininess();
            UniformBufferManager::GetInstance().UpdateUniformBuffer(uboName, &props, sizeof(props));
        }
    }
}

void Renderer::RenderScene(const SceneNode& rootNode) {
    sceneGraphRenderer->RenderScene(rootNode);
}

void Renderer::FinishFrame() {                                                        // Finish frame
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace RavenEngine