// GLFWWindowWrapper.cpp

// #include section
// #################
// Standard library includes
#include <iostream>

// local project includes
#include "GLFWWindowWrapper.h"


GLFWWindowWrapper::GLFWWindowWrapper(int width, int height, const char* title)    // Constructor
    : mainWindow(nullptr), isWindowInitialized(false) {
    initGLFW();                                                                   // Initialize GLFW
    mainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);        // Create the GLFW window
    if (!mainWindow) {                                                            // Check if the window was created successfully
        // Replace with your actual exception handling
        throw std::runtime_error("Failed to create GLFW window");                 // Throw an exception if the window was not created successfully
    }
    isWindowInitialized = true;                                                   // Set the isWindowInitialized flag to true
}

void GLFWWindowWrapper::initGLFW() {                                              // Initialize GLFW function
    if (!glfwInit()) {                                                            // Check if GLFW was initialized successfully
        // Replace with your actual exception handling
        throw std::runtime_error("Failed to initialize GLFW");                    // Throw an exception if GLFW was not initialized successfully
    }
}

GLFWWindowWrapper::~GLFWWindowWrapper() {                                         // Destructor
    cleanUp();                                                                    // Clean up the GLFWWindowWrapper
}

void GLFWWindowWrapper::setWindowProperties(GLFWwindow* window) {                 // Set window properties function (empty to be implemented by the user)
    // Set window properties here
    // left empty to be implemented by the user
}

GLFWwindow* GLFWWindowWrapper::getMainWindow() const {                            // Get the GLFWwindow pointer function
    return mainWindow;                                                            // Return the GLFWwindow pointer
}

bool GLFWWindowWrapper::shouldClose() const {                                     // Check if the window should close function
    return glfwWindowShouldClose(mainWindow);                                     // Return the result of glfwWindowShouldClose
}

void GLFWWindowWrapper::swapBuffers() {                                           // Swap the window buffers function
    if (mainWindow) {                                                             // Check if the window was created successfully
        glfwSwapBuffers(mainWindow);                                              // Swap the window buffers
    }
}

void GLFWWindowWrapper::cleanUp() {                                               // Clean up the GLFWWindowWrapper function
    if (mainWindow) {                                                             // Check if the window was created successfully
        glfwDestroyWindow(mainWindow);                                            // Destroy the GLFW window
        mainWindow = nullptr;                                                     // Set the GLFWwindow pointer to nullptr
    }
    if (isWindowInitialized) {                                                    // Check if the window was initialized successfully
        glfwTerminate();                                                          // Terminate GLFW
    }
}