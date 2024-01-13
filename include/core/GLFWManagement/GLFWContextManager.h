#ifndef GLFW_CONTEXT_MANAGER_H
#define GLFW_CONTEXT_MANAGER_H

#include "GLFWWindowWrapper.h"
#include <GLFW/glfw3.h>

class GLFWContextManager {
public:
    GLFWContextManager(GLFWwindow* window);
    void makeContextCurrent(GLFWwindow* window);
    
private:
    void loadGLAD();
};

#endif // GLFW_CONTEXT_MANAGER_H
