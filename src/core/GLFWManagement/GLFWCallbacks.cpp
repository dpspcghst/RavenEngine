// Standard library headers
#include <iostream> // For std::cout, std::endl

// Project headers
#include "GLFWCallbacks.h" // For GLFWCallbacks class definition

// Function: keyCallback
// Description: Handles key events
// Parameters: 
// - window: The window that received the event
// - key: The keyboard key that was pressed or released
// - scancode: The system-specific scancode of the key
// - action: The key action (GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT)
// - mods: Bit field describing which modifier keys were held down
void GLFWCallbacks::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // key callback implementation
}

// Function: windowSizeCallback
// Description: Handles window resize events
// Parameters: 
// - window: The window that was resized
// - width: The new width, in screen coordinates, of the window
// - height: The new height, in screen coordinates, of the window
void GLFWCallbacks::windowSizeCallback(GLFWwindow* window, int width, int height) {
    // window size callback implementation
}