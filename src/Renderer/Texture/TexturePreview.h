// texturepreview.h
#ifndef TEXTURE_PREVIEW_H
#define TEXTURE_PREVIEW_H

// #include section
// #####################
// Standard library includes
#include <string>

// Third-party includes
#include <glad/glad.h>

// Raven includes

namespace RavenEngine {

class TexturePreview {
public:
    // Constructor: Load texture and generate preview
    TexturePreview(const std::string& texturePath);

    // Destructor: Clean up resources
    ~TexturePreview();

    // Render the texture preview as a thumbnail
    void DrawThumbnail(const float thumbnailSize);

private:
    GLuint textureID; // OpenGL texture ID
    int width, height; // Texture dimensions

    // Load texture from file
    bool LoadTexture(const std::string& texturePath);

    // Delete texture to clean up resources
    void DeleteTexture();
};

} // namespace RavenEngine

#endif // TEXTURE_PREVIEW_H
