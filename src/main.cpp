// main.cpp
// #################
// #include section
// #################
// Standard library includes
#include <iostream>

// Third-party library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Raven includes
#include "core/GameLoop.h"
#include "../Settings/SettingsManager.h"
#include "../include/core/Workspace.h"
#include "GLFWContextManager.h"
#include "GLFWEventPoller.h"
#include "GLFWWindowWrapper.h"
#include "ImGuiManager.h"
#include "ResourceManager.h"
#include "GameStateManager.h"

int main() {
    try {
        auto& settingsManager = RavenEngine::SettingsManager::GetInstance(); // Settings Singleton
        GLFWWindowWrapper windowWrapper(800, 600, "Raven Engine"); // Window Wrapper
        GLFWwindow* mainWindow = windowWrapper.getMainWindow(); // Main Window
        glfwMaximizeWindow(mainWindow); // Maximize the window
        GLFWContextManager contextManager(mainWindow); // Context Manager for OpenGL (GLAD and GLFW)
        RavenEngine::ResourceManager::LoadIcon(mainWindow, L"../Assets/images/icons/ravenIco.ico"); // Load App Icon
        RavenEngine::ResourceManager::SetWindowIcons(mainWindow); // Set App Icon

        const GLubyte* glVersion = glGetString(GL_VERSION); // Get OpenGL version
        std::cout << "OpenGL version: " << (glVersion ? (const char*)glVersion : "Failed to get OpenGL version") << std::endl;

        ImGuiManager::Init(mainWindow); // Initialize ImGui
        RavenEngine::Workspace workspace(mainWindow); // Workspace
        RavenEngine::GameLoop gameLoop; // Game Loop


        while (!windowWrapper.shouldClose()) { // Main Loop
            GLFWEventPoller::pollEvents(); // Poll Events
            ImGuiManager::NewFrame(); // Start ImGui Frame

            auto gameState = RavenEngine::GameStateManager::GetInstance().GetState();

            if (gameState == RavenEngine::GameState::Running) { // if runGameLoop is true, run the game loop
                float frameRate = settingsManager.GetFrameRate();
                float deltaTime = static_cast<float>(1.0 / frameRate); // Calculate deltaTime
                gameLoop.Update(deltaTime); // Update Game Loop with deltaTime
            }

            workspace.Render(); // Render Workspace
            ImGuiManager::Render(); // Render ImGui
            windowWrapper.swapBuffers(); // Swap Buffers
        }

        ImGuiManager::Shutdown(); // Shutdown ImGui
        RavenEngine::ResourceManager::UnloadIcon(); // Unload App Icon
    } catch (const std::exception& e) { // Catch exceptions
        std::cerr << "Error: " << e.what() << std::endl; // Print error message
        return EXIT_FAILURE; // Return EXIT_FAILURE
    }
    return EXIT_SUCCESS; // Return EXIT_SUCCESS
}