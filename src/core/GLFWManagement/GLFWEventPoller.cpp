// GLFWEventPoller.cpp

// Project headers
#include "GLFWEventPoller.h" // For GLFWEventPoller class definition

// Third-party headers
#include <GLFW/glfw3.h> // For glfwPollEvents function

// Function: pollEvents
// Description: Polls for pending events in the GLFW event queue
void GLFWEventPoller::pollEvents() {
    glfwPollEvents();
}