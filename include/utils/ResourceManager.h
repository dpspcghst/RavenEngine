#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

// Third-party headers
#include <GLFW/glfw3.h> // For GLFWwindow

// Windows headers
#include <Windows.h> // For HICON, LPCWSTR

// Class: ResourceManager
// Description: Manages resources such as window icons
class ResourceManager {
public:
    // Function: LoadIcon
    // Description: Loads the window icons from the specified file paths
    // Parameters: 
    // - window: The GLFW window to set the icons for
    // - iconPath16: The file path of the 16x16 icon
    // - iconPath32: The file path of the 32x32 icon
    static void LoadIcon(GLFWwindow* window, LPCWSTR iconPath16, LPCWSTR iconPath32);

    // Function: SetWindowIcons
    // Description: Sets the loaded window icons for the specified GLFW window
    // Note: This function should be called after calling LoadIcon
    // Parameters: window - The GLFW window to set the icons for
    static void SetWindowIcons(GLFWwindow* window);

    // Function: UnloadIcon
    // Description: Unloads the loaded window icons
    // Note: This function should be called when the icons are no longer needed
    static void UnloadIcon();

private:
    static HICON smallIcon; // The handle to the small icon
    static HICON largeIcon; // The handle to the large icon
};

#endif // RESOURCE_MANAGER_H