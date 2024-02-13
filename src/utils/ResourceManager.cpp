// resourcemanager.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <Windows.h>
#include <iostream>
// Third party includes/definitions
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
// Raven includes
#include "ResourceManager.h"

namespace RavenEngine {
HICON ResourceManager::smallIcon = nullptr; // Initialize the small icon
HICON ResourceManager::largeIcon = nullptr; // Initialize the large icon

void ResourceManager::LoadIcon(GLFWwindow* window, LPCWSTR iconPath) {  // Load the window icons
    wchar_t fullIconPath[MAX_PATH]; // The full path to the icon
    
    GetFullPathNameW(iconPath, MAX_PATH, fullIconPath, nullptr); // Get the full path to the icon

    smallIcon = (HICON)LoadImageW(NULL, fullIconPath, IMAGE_ICON, 32, 32, LR_LOADFROMFILE); // Load the small icon
    if (smallIcon == nullptr) { // If the small icon fails to load
        std::cerr << "Failed to load small icon. Error: " << GetLastError() << std::endl;
    }

    largeIcon = (HICON)LoadImageW(NULL, fullIconPath, IMAGE_ICON, 64, 64, LR_LOADFROMFILE); // Load the large icon
    if (largeIcon == nullptr) { // If the large icon fails to load
        std::cerr << "Failed to load large icon. Error: " << GetLastError() << std::endl;
    }
}

void ResourceManager::UnloadIcon() {                                                          // Unload the window icons
    if (smallIcon) { // If the small icon exists
        DestroyIcon(smallIcon); // Destroy the small icon
        smallIcon = nullptr; // Set the small icon to nullptr
    }
    
    if (largeIcon) { // If the large icon exists
        DestroyIcon(largeIcon); // Destroy the large icon
        largeIcon = nullptr; // Set the large icon to nullptr
    }
}

void ResourceManager::SetWindowIcons(GLFWwindow* window) {                                   // Set the window icons
    HWND hwnd = glfwGetWin32Window(window); // Get the window handle
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)smallIcon); // Set the small icon
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)largeIcon); // Set the large icon
}

} // namespace RavenEngine