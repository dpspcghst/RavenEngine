// texturemanager.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
#include <fstream>
// Third-party includes
#include <glad/glad.h>
#include <stb_image.h>
// Raven includes
#include "TextureManager.h"

namespace RavenEngine {

TextureManager& TextureManager::GetInstance() {
    static TextureManager instance;
    return instance;
}

TextureManager::TextureManager() : nextId(1) {  // Initialize nextId to 1
    std::cout << "TextureManager Initialized" << std::endl;
}

TextureManager::~TextureManager() {
    for (auto& pair : textures) {
        glDeleteTextures(1, &pair.second.id);
        std::cout << "TextureManager::Destructor - Deleted Texture ID: " << pair.first << std::endl;
    }
}

int TextureManager::LoadTexture(std::string filename, bool generateMipMaps) {
    std::cout << "Loading Texture from file: " << filename << std::endl;
    std::cout << "TextureManager::LoadTexture current id: " << nextId << std::endl;

    if (!std::ifstream(filename).good()) {
        std::cerr << "TextureManager::LoadTexture - File not found: " << filename << std::endl;
        return -1;
    } else {
        std::cout << "TextureManager::LoadTexture - File found: " << filename << std::endl;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "TextureManager::LoadTexture - Failed to load texture: " << filename << std::endl;
        return -1;
    } else {
        std::cout << "TextureManager::LoadTexture - Texture loaded successfully: " << filename << std::endl;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLenum format = GL_RGB;
    if (nrChannels == 1) format = GL_RED;
    else if (nrChannels == 3) format = GL_RGB;
    else if (nrChannels == 4) format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    if (generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    int assignedId = nextId++;
    textures[assignedId] = {texture, 1.0f};
    std::cout << "TextureManager::LoadTexture - Assigned Texture ID: " << assignedId << " to file: " << filename << std::endl;
    std::cout << "TextureManager::LoadTexture - nextId after increment: " << nextId << std::endl;

    // Print the current state of the textures map
    std::cout << "TextureManager::LoadTexture - Current state of textures map:\n";
    for (const auto& pair : textures) {
        std::cout << "  Texture ID: " << pair.first << ", Texture Info: { id: " << pair.second.id << ", alpha: " << pair.second.alpha << " }\n";
    }
    return assignedId;
}

bool TextureManager::UnloadTexture(int id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        glDeleteTextures(1, &it->second.id);
        textures.erase(it);
        std::cout << "TextureManager::UnloadTexture - Unloaded Texture ID: " << id << std::endl;
        return true;
    } else {
        std::cerr << "TextureManager::UnloadTexture - Texture ID not found: " << id << std::endl;
        return false;
    }
}

TextureInfo TextureManager::GetTexture(int id) const {
    auto it = textures.find(id);
    if (it == textures.end()) {
        std::cerr << "TextureManager::GetTexture - Texture ID not found: " << id << std::endl;
        return {0, 1.0f}; // Default texture info for non-existent ID
    }
    std::cout << "TextureManager::GetTexture - Accessed Texture ID: " << id << std::endl;
    return it->second;
}

int TextureManager::GetTextureId(std::string textureName) {
    // Iterate over the idToName map
    for (const auto& pair : idToName) {
        if (pair.second == textureName) {
            return pair.first; // Return the ID if the name matches
        }
    }
    // Return -1 or throw an exception if the texture name is not found
    return -1;
}

float TextureManager::GetTextureAlpha(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.alpha;
    }
    std::cerr << "TEXTIREMANAGER::GETTEXTUREALPHA Texture with id " << id << " not found." << std::endl;
    return 1.0f;
}

bool TextureManager::SetTextureAlpha(int id, float alpha) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.alpha = alpha;
        return true;
    } else {
        std::cerr << "TEXTIREMANAGER::SETTEXTUREALPHA Texture with id " << id << " not found." << std::endl;
        return false;
    }
}

bool TextureManager::HasTexture(int id) const {
    return textures.find(id) != textures.end();
}

} // namespace RavenEngine