#ifndef GLFW_WINDOW_WRAPPER_H
#define GLFW_WINDOW_WRAPPER_H

#include <GLFW/glfw3.h>

class GLFWWindowWrapper {
public:
    GLFWWindowWrapper(int width, int height, const char* title);
    ~GLFWWindowWrapper();
    GLFWwindow* getMainWindow() const;
    void setWindowProperties(GLFWwindow* window);
    bool shouldClose() const;
    void swapBuffers();
    
private:
    void initGLFW();
    void cleanUp();
    GLFWwindow* mainWindow;
    bool isWindowInitialized;
};

#endif // GLFW_WINDOW_WRAPPER_H