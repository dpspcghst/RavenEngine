// main.cpp

// #include section
// #################
// Standard library includes
#include <iostream>

// Third-party library includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Local project includes
#include "../Settings/SettingsManager.h"
#include "../include/core/Workspace.h"
#include "GLFWContextManager.h"
#include "GLFWEventPoller.h"
#include "GLFWWindowWrapper.h"
#include "ImGuiManager.h"
#include "ResourceManager.h"

// main function
int main() { 
    try {                                                                                   // Try to run the code
        auto& settingsManager = RavenEngine::SettingsManager::GetInstance();        
        GLFWWindowWrapper windowWrapper(800, 600, "Raven Engine");                          // Initialize the GLFWWindowWrapper
        GLFWwindow* mainWindow = windowWrapper.getMainWindow();                             // Get the GLFWwindow pointer from the GLFWWindowWrapper
        glfwMaximizeWindow(mainWindow);                                                     // Maximize the window
        GLFWContextManager contextManager(mainWindow);                                      // Initialize the GLFWContextManager

        ResourceManager::LoadIcon(mainWindow, L"../Assets/Images/Icons/raven16x16.ico", 
                                              L"../Assets/Images/Icons/raven32x32.ico");    // Load the window icons
        ResourceManager::SetWindowIcons(mainWindow);                                        // Set the window icons

        ImGuiManager::Init(mainWindow);                                                     // Initialize the ImGuiManager
        RavenEngine::Workspace workspace(mainWindow);  // Initialize the Workspace                      // Initialize the Workspace
        //std::cout << "starting main loop" << std::endl;                                     // Output "starting main loop
        while (!windowWrapper.shouldClose()) {                                              // Main loop
            GLFWEventPoller::pollEvents();                                                  // Poll GLFW events
            ImGuiManager::NewFrame();                                                       // Start the Dear ImGui frame
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());                         // Dock the ImGui window
            workspace.Render();                                                             // Render the Workspace
            ImGuiManager::Render();                                                         // Render the ImGui frame
            windowWrapper.swapBuffers();                                                    // Swap the window buffers
        }

        ImGuiManager::Shutdown();                                                           // Shutdown the ImGuiManager
        ResourceManager::UnloadIcon();                                                      // Unload the window icons
    } catch (const std::exception& e) {                                                     
        std::cerr << "Error: " << e.what() << std::endl;                                    // Catch any exceptions and print the error message
        return EXIT_FAILURE;                                                                // Return EXIT_FAILURE
    }
    return EXIT_SUCCESS;                                                                    // Return EXIT_SUCCESS
}