#ifndef GLFW_CALLBACKS_H
#define GLFW_CALLBACKS_H

#include <GLFW/glfw3.h>

class GLFWCallbacks {
public:
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowSizeCallback(GLFWwindow* window, int width, int height);
};

#endif // GLFW_CALLBACKS_H
