// Standard library headers
#include <stdexcept> // For std::runtime_error

// Third-party headers
#include <glad/glad.h> // For gladLoadGLLoader function

// Project headers
#include "GLFWContextManager.h" // For GLFWContextManager class definition

// Constructor: Initializes the GLFWContextManager with a GLFWwindow
// Parameters: window - The GLFWwindow to make the context current
GLFWContextManager::GLFWContextManager(GLFWwindow* window) {
    makeContextCurrent(window);
    loadGLAD();
}

// Function: makeContextCurrent
// Description: Makes the context of the specified window current
// Parameters: window - The GLFWwindow to make the context current
void GLFWContextManager::makeContextCurrent(GLFWwindow* window) {
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Set the swap interval
}

// Function: loadGLAD
// Description: Loads GLAD
void GLFWContextManager::loadGLAD() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}