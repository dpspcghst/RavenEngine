#include "GLFWEventPoller.h"
#include <GLFW/glfw3.h>

void GLFWEventPoller::pollEvents() {
    glfwPollEvents();
}
