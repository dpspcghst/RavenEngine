// TextureFileDialog.cpp
// #include section
// #####################
// Standard library includes

// Third-party includes

// Raven includes
#include "FileDialog.h"
#include "TextureFileDialog.h"

namespace RavenEngine {
std::string TextureFileDialog::OpenTextureDialog(GLFWwindow* ownerWindow) {
    // Define the filter string for image files
    std::wstring filter =
        L"";
    return FileDialog::OpenFileDialog(ownerWindow, filter);
}
}
