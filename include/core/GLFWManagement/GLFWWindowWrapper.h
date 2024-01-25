#ifndef GLFW_WINDOW_WRAPPER_H
#define GLFW_WINDOW_WRAPPER_H

// Third-party includes
#include <GLFW/glfw3.h> // For GLFWwindow

// Class: GLFWWindowWrapper
// Description: Wraps the GLFW window functionality
class GLFWWindowWrapper {
public:
    // Constructor: Initializes the GLFWWindowWrapper with width, height, and title
    // Parameters: width - The width of the window, height - The height of the window, title - The title of the window
    GLFWWindowWrapper(int width, int height, const char* title);

    // Destructor: Cleans up the GLFWWindowWrapper
    ~GLFWWindowWrapper();

    // Function: getMainWindow
    // Description: Returns the GLFWwindow pointer
    // Returns: The GLFWwindow pointer
    GLFWwindow* getMainWindow() const;

    // Function: setWindowProperties
    // Description: Sets the window properties (to be implemented by the user)
    // Parameters: window - The GLFWwindow to set the properties for
    void setWindowProperties(GLFWwindow* window);

    // Function: shouldClose
    // Description: Checks if the window should close
    // Returns: true if the window should close, false otherwise
    bool shouldClose() const;

    // Function: swapBuffers
    // Description: Swaps the window buffers
    void swapBuffers();
    
private:
    // Function: initGLFW
    // Description: Initializes GLFW
    void initGLFW();

    // Function: cleanUp
    // Description: Cleans up the GLFWWindowWrapper
    void cleanUp();

    // Member to store the GLFWwindow pointer
    GLFWwindow* mainWindow;

    // Flag to indicate if the window was initialized successfully
    bool isWindowInitialized;
};

#endif // GLFW_WINDOW_WRAPPER_H