#include "GLFWWindowWrapper.h"
#include <iostream>

GLFWWindowWrapper::GLFWWindowWrapper(int width, int height, const char* title)
    : mainWindow(nullptr), isWindowInitialized(false) {
    initGLFW();
    mainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!mainWindow) {
        // Replace with your actual exception handling
        throw std::runtime_error("Failed to create GLFW window");
    }
    isWindowInitialized = true;
}

void GLFWWindowWrapper::initGLFW() {
    if (!glfwInit()) {
        // Replace with your actual exception handling
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

GLFWWindowWrapper::~GLFWWindowWrapper() {
    cleanUp();
}

void GLFWWindowWrapper::setWindowProperties(GLFWwindow* window) {
    // Set properties specific to the window
    // For example:
    // glfwSetWindowSizeLimits(window, 800, 600, GLFW_DONT_CARE, GLFW_DONT_CARE);
}

GLFWwindow* GLFWWindowWrapper::getMainWindow() const {
    return mainWindow;
}

bool GLFWWindowWrapper::shouldClose() const {
    return glfwWindowShouldClose(mainWindow);
}

void GLFWWindowWrapper::swapBuffers() {
    if (mainWindow) {
        glfwSwapBuffers(mainWindow);
    }
}

void GLFWWindowWrapper::cleanUp() {
    if (mainWindow) {
        glfwDestroyWindow(mainWindow);
        mainWindow = nullptr;
    }
    if (isWindowInitialized) {
        glfwTerminate();
    }
}