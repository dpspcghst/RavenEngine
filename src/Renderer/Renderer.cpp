// render.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third party includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

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
#include "../../include/core/GameStateManager.h"

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

std::pair<int, int> Renderer::GetSize() const {                                       // Get size
    return std::make_pair(gameWidth, gameHeight);
}

void Renderer::SetGLViewport(int x, int y, int width, int height) {                   // Set GL viewport
    glViewport(x, y, width, height);
    gameWidth = width;
    gameHeight = height;
}

GLuint Renderer::GetCurrentTexture() {                                                // Get current texture
    GLuint currentTexture = fbManager->GetCurrentTexture();
    std::cout << "GetCurrentTexture: " << currentTexture << std::endl;
    return currentTexture;
}

// Initialize Renderer
bool Renderer::InitializeRenderer() {                                                 // Initialize renderer

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

}

void Renderer::StartFrame() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbManager->GetCurrentTexture());

    // Check the game state and set the clear color accordingly
    switch (GameStateManager::GetInstance().GetState()) {
        case GameState::Running:
            // Set the clear color to black when the game is running
            clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
            glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);

            // Reset the pause timer
            pauseTimer = 0.0f;
            break;

        case GameState::Paused:
            // Render the paused screen when the game is paused
            RenderPausedScreen();
            break;

        case GameState::Stopped:
        default:
            // Set the clear color to blue when the game is not running (i.e., in Edit Mode)
            clearColor = {0.149f, 0.137f, 0.788f, 1.0f};
            glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);

            // Reset the pause timer
            pauseTimer = 0.0f;
            break;
    }
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

void Renderer::RenderPausedScreen() {
    // Increment the pause timer by the time since the last frame
    pauseTimer += ImGui::GetIO().DeltaTime;

    // Render a pause message or overlay if the timer is less than 2 seconds
    if (pauseTimer <= 2.0f) {
        ImGui::Begin("PauseOverlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
        ImGui::SetWindowFontScale(2.0); // Increase font size for visibility
        ImGui::Text("Game Paused");
        ImGui::End();
    }
}

void Renderer::FinishFrame() {                                                        // Finish frame
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

} // namespace RavenEngine