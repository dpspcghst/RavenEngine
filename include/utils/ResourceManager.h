// resourcemanager.h
// #####################
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
// #####################
// #include section
// #####################
// Standard library includes
#include <Windows.h> // For HICON, LPCWSTR
// Third-party includes
#include <GLFW/glfw3.h> // For GLFWwindow
// Raven includes
namespace RavenEngine {
class ResourceManager {
public:
    static void LoadIcon(GLFWwindow* window, LPCWSTR iconPath); // Load the window icons
    static void SetWindowIcons(GLFWwindow* window); // Set the window icons
    static void UnloadIcon(); // Unload the window icons

    void LoadTexture(const char* texturePath); // Load a texture

private:
    static HICON smallIcon; // The handle to the small icon
    static HICON largeIcon; // The handle to the large icon
};

} // namespace RavenEngine

#endif // RESOURCE_MANAGER_H
