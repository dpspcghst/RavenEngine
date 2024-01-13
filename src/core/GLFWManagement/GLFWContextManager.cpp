#include <iostream>
#include "glad/glad.h"
#include "GLFWContextManager.h"

GLFWContextManager::GLFWContextManager(GLFWwindow* window) {
    makeContextCurrent(window);
    loadGLAD();
}

void GLFWContextManager::makeContextCurrent(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Add this line to set the swap interval
}

void GLFWContextManager::loadGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}