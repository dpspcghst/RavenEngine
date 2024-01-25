// Windows headers
#include <Windows.h> // For HICON, LPCWSTR, MAX_PATH, GetFullPathNameW, LoadImageW, DestroyIcon, SendMessage, WM_SETICON, ICON_SMALL, ICON_BIG

// Define GLFW_EXPOSE_NATIVE_WIN32 to expose native GLFW functions
#define GLFW_EXPOSE_NATIVE_WIN32

// Third-party headers
#include <GLFW/glfw3.h> // For GLFWwindow
#include <GLFW/glfw3native.h> // For glfwGetWin32Window

// Project headers
#include "ResourceManager.h" // For ResourceManager class definition

// Standard library headers
#include <iostream> // For std::cerr, std::endl

// Initialize static members
HICON ResourceManager::smallIcon = nullptr;
HICON ResourceManager::largeIcon = nullptr;

// Function: LoadIcon
// Description: Loads the small and large icons from the specified paths
// Parameters: 
// - window: The window to load the icons for
// - iconPath16: The path to the 16x16 icon
// - iconPath32: The path to the 32x32 icon
void ResourceManager::LoadIcon(GLFWwindow* window, LPCWSTR iconPath16, LPCWSTR iconPath32) {
    wchar_t fullIconPath16[MAX_PATH];
    wchar_t fullIconPath32[MAX_PATH];
    GetFullPathNameW(iconPath16, MAX_PATH, fullIconPath16, nullptr);
    GetFullPathNameW(iconPath32, MAX_PATH, fullIconPath32, nullptr);

    smallIcon = (HICON)LoadImageW(NULL, fullIconPath16, IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
    if (smallIcon == nullptr) {
        std::cerr << "Failed to load small icon. Error: " << GetLastError() << std::endl;
    }

    largeIcon = (HICON)LoadImageW(NULL, fullIconPath32, IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
    if (largeIcon == nullptr) {
        std::cerr << "Failed to load large icon. Error: " << GetLastError() << std::endl;
    }
}

// Function: UnloadIcon
// Description: Unloads the small and large icons
void ResourceManager::UnloadIcon() {
    if (smallIcon) {
        DestroyIcon(smallIcon);
        smallIcon = nullptr;
    }
    
    if (largeIcon) {
        DestroyIcon(largeIcon);
        largeIcon = nullptr;
    }
}

// Function: SetWindowIcons
// Description: Sets the small and large icons for the window
// Parameters: window - The window to set the icons for
void ResourceManager::SetWindowIcons(GLFWwindow* window) {
    HWND hwnd = glfwGetWin32Window(window);
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)smallIcon);
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)largeIcon);
}