#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "GLFWWindowWrapper.h"
#include "GLFWContextManager.h"
#include "GLFWEventPoller.h"
#include "ImGuiManager.h"
#include "ResourceManager.h"
#include "../include/core/Workspace.h" // Make sure the path is correct

int main() { 
    try {
        GLFWWindowWrapper windowWrapper(800, 600, "Raven Engine");
        GLFWwindow* mainWindow = windowWrapper.getMainWindow();
        glfwMaximizeWindow(mainWindow);
        GLFWContextManager contextManager(mainWindow);

        ResourceManager::LoadIcon(mainWindow, L"../Assets/Images/Icons/raven16x16.ico", 
                                              L"../Assets/Images/Icons/raven32x32.ico");
        ResourceManager::SetWindowIcons(mainWindow);

        ImGuiManager::Init(mainWindow);
        RavenEngine::Workspace workspace(mainWindow); // Assuming Workspace is in the RavenEngine namespace

        while (!windowWrapper.shouldClose()) {
            GLFWEventPoller::pollEvents(); 
            ImGuiManager::NewFrame(); 
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); 
            workspace.Render(); 
            ImGuiManager::Render();
            windowWrapper.swapBuffers();
        }

        ImGuiManager::Shutdown();
        ResourceManager::UnloadIcon();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
