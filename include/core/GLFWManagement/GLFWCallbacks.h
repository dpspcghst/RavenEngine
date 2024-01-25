#ifndef GLFW_CALLBACKS_H
#define GLFW_CALLBACKS_H

// Third-party headers
#include <GLFW/glfw3.h> // For GLFWwindow

// Class: GLFWCallbacks
// Description: Handles GLFW callbacks
class GLFWCallbacks {
public:
    // Function: keyCallback
    // Description: Handles key events
    // Parameters: 
    // - window: The window that received the event
    // - key: The keyboard key that was pressed or released
    // - scancode: The system-specific scancode of the key
    // - action: The key action (GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT)
    // - mods: Bit field describing which modifier keys were held down
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // Function: windowSizeCallback
    // Description: Handles window resize events
    // Parameters: 
    // - window: The window that was resized
    // - width: The new width, in screen coordinates, of the window
    // - height: The new height, in screen coordinates, of the window
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
};

#endif // GLFW_CALLBACKS_H