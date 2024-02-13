// filedialog.h
#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

// #include section
// #####################
// Standard library includes
#include <string>
// Third-party library includes
#include <GLFW/glfw3.h>
// Raven includes

namespace RavenEngine {
class FileDialog {
public:
    static std::string OpenFileDialog(GLFWwindow* ownerWindow, const std::wstring& filter);
};
} // namespace RavenEngine
#endif // FILE_DIALOG_H
