#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

// Third-party headers
#include <GLFW/glfw3.h> // For GLFWwindow

// Project headers
#include "GLFWWindowWrapper.h" // For GLFWWindowWrapper class definition

// Class: GLFWContextManager
// Description: Manages the GLFW context
class GLFWContextManager {
public:
    // Constructor: Initializes the GLFWContextManager with a GLFWwindow
    // Parameters: window - The GLFWwindow to make the context current
    GLFWContextManager(GLFWwindow* window);

    // Function: makeContextCurrent
    // Description: Makes the context of the specified window current
    // Parameters: window - The GLFWwindow to make the context current
    void makeContextCurrent(GLFWwindow* window);
    
private:
    // Function: loadGLAD
    // Description: Loads GLAD
    void loadGLAD();
};

#endif // GLFW_CONTEXT_MANAGER_H