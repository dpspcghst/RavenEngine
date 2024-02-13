// texturepreview.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>

// Third-party includes
#include <imgui.h>
#include <stb_image.h>

// Raven includes
#include "TexturePreview.h"

namespace RavenEngine {

TexturePreview::TexturePreview(const std::string& texturePath)
    : textureID(0), width(0), height(0) {
    if (!LoadTexture(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

TexturePreview::~TexturePreview() {
    DeleteTexture();
}

bool TexturePreview::LoadTexture(const std::string& texturePath) {

    // Load image data with 4 channels (RGBA) per pixel
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, NULL, 4); // NULL for channels to default to 4
    if (data == nullptr) {
        std::cerr << "Texture failed to load at path: " << texturePath << std::endl;
        return false;
    }
    int nrChannels = 4; // 4 channels for RGBA

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Determine the image format
    GLenum format = GL_RGB;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;

    // Upload the image data to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D); // Optional: Generate mipmaps for the texture

    // Free the loaded data because it's now on the GPU
    stbi_image_free(data);
    return true;
}

void TexturePreview::DeleteTexture() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
        textureID = 0;
    }
}

void TexturePreview::DrawThumbnail(const float thumbnailSize) {
    if (textureID == 0) return;
    // Draw the texture with default UV coordinates
    ImGui::Image((void*)(intptr_t)textureID, ImVec2(thumbnailSize, thumbnailSize), ImVec2(0, 0), ImVec2(1, 1));
}

} // namespace RavenEngine