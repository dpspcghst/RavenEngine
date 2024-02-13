// TextureFileDialog.h
#ifndef TEXTURE_FILE_DIALOG_H
#define TEXTURE_FILE_DIALOG_H

// #include section
// #####################
// Standard library includes
#include <string>
// Third-party library includes
#include <GLFW/glfw3.h>
// Raven includes

namespace RavenEngine {
class TextureFileDialog {
public:
    // This could be a static method if you're following a singleton-like approach for FileDialog
    static std::string OpenTextureDialog(GLFWwindow* ownerWindow);
};
} // namespace RavenEngine
#endif // TEXTURE_FILE_DIALOG_H
