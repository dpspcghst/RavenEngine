// texturemanager.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
#include <fstream>
#include <filesystem>
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

TextureManager::TextureManager() : nextId(1) {
    std::cout << "TextureManager Initialized" << std::endl;
}

TextureManager::~TextureManager() {
    for (auto& pair : textures) {
        glDeleteTextures(1, &pair.second.id);
        std::cout << "TextureManager::Destructor - Deleted Texture ID: " << pair.first << std::endl;
    }
}

GLuint TextureManager::GenerateTexture(unsigned char* data, int width, int height, int nrChannels, bool generateMipMaps) {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Determine the format based on the number of channels
    GLenum format = GL_RGB;
    if (nrChannels == 1) format = GL_RED;
    else if (nrChannels == 3) format = GL_RGB;
    else if (nrChannels == 4) format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    if (generateMipMaps) glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

int TextureManager::LoadTexture(std::string filename, bool generateMipMaps) {
    std::cout << "Loading Texture from file: " << filename << std::endl;

    if (!std::ifstream(filename).good()) {
        std::cerr << "TextureManager::LoadTexture - File not found: " << filename << std::endl;
        return -1;
    }

    int width, height, nrChannels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "TextureManager::LoadTexture - Failed to load texture: " << filename << std::endl;
        return -1;
    }

    GLuint texture = GenerateTexture(data, width, height, nrChannels, generateMipMaps);
    stbi_image_free(data);

    // Create a TextureInfo object and set its fields individually
    TextureInfo textureInfo;
    textureInfo.id = texture;
    textureInfo.filteringMode = GL_LINEAR; // Default filtering mode
    textureInfo.wrapModeS = GL_REPEAT; // Default wrap mode S
    textureInfo.wrapModeT = GL_REPEAT; // Default wrap mode T
    textureInfo.filename = std::filesystem::path(filename).filename().string();

    int assignedId = nextId++; // Assign the next available ID
    textures[assignedId] = textureInfo; // Assign the texture info object to the map

    std::cout << "TextureManager::LoadTexture - Assigned Texture ID: " << assignedId << " to file: " << filename << "with alpha:" << textureInfo.alpha << std::endl;

    return assignedId;
}

bool TextureManager::HasTexture(int id) const {
    return textures.find(id) != textures.end();
}

void TextureManager::BindTexture(int id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        glBindTexture(GL_TEXTURE_2D, it->second.id);
    } else {
        std::cerr << "TextureManager::BindTexture - Texture ID not found: " << id << std::endl;

        // Print out the IDs of all the textures in the map
        std::cerr << "Current texture IDs: ";
        for (const auto& pair : textures) {
            std::cerr << pair.first << " ";
        }
        std::cerr << std::endl;
    }
}

void TextureManager::UnbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
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
    std::cout << "TEXTUREMANAGER::GETTEXTURE getting id: " << id << std::endl;
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second;
    } else {
        std::cerr << "TextureManager::GetTexture - Texture ID not found: " << id << std::endl;
        // Create a TextureInfo object with default values
        TextureInfo defaultTextureInfo;
        return defaultTextureInfo;
    }
}

int TextureManager::GetTextureId(std::string textureName) {
    for (const auto& pair : idToName) {
        if (pair.second == textureName) {
            return pair.first;
        }
    }
    return -1;
}

std::vector<std::string> TextureManager::GetLoadedTextureFiles() const {
    std::vector<std::string> filepaths;
    for (const auto& pair : textures) {
        filepaths.push_back(pair.second.filepath);
    }
    return filepaths;
}

// set/get alpha value
float TextureManager::GetTextureAlpha(int id) const {
    std::cout << "TEXTUREMANAGER::GETTEXTUREALPHA getting id: " << id << "with alpha:" << textures.find(id)->second.alpha << std::endl;
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.alpha;
    }
    std::cerr << "TEXTUREMANAGER::GETTEXTUREALPHA - Texture with id " << id << " not found." << std::endl;
    return 1.0f;
}

bool TextureManager::SetTextureAlpha(int id, float alpha) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.alpha = alpha;
        return true;
    } else {
        std::cerr << "TEXTUREMANAGER::SETTEXTUREALPHA - Texture with id " << id << " not found." << std::endl;
        return false;
    }
}

// set/get texture scale
void TextureManager::SetTextureScale(int id, float scaleX, float scaleY) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.scaleX = scaleX;
        it->second.scaleY = scaleY;
    }
}

float TextureManager::GetTextureScaleX(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.scaleX;
    }
    return 1.0f; // Default scale if not found
}

float TextureManager::GetTextureScaleY(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.scaleY;
    }
    return 1.0f; // Default scale if not found
}

void TextureManager::SetTexturePosition(int id, glm::vec2 position) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.position = position;
    }
}

glm::vec2 TextureManager::GetTexturePosition(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.position;
    }
    return glm::vec2(0.0f, 0.0f); // Default position
}

void TextureManager::SetTextureRotation(int id, float rotation) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.rotation = rotation;
    }
}

float TextureManager::GetTextureRotation(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.rotation;
    }
    return 0.0f; // Default rotation
}

// set/get filtering mode
void TextureManager::SetTextureFilteringMode(int id, GLenum mode) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.filteringMode = mode;
        glBindTexture(GL_TEXTURE_2D, it->second.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mode);
    } else {
        std::cerr << "TextureManager::SetTextureFilteringMode - Texture ID not found: " << id << std::endl;
    }
}

GLenum TextureManager::GetTextureFilteringMode(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.filteringMode;
    }
    std::cerr << "TextureManager::GetTextureFilteringMode - Texture ID not found: " << id << std::endl;
    return GL_LINEAR; // Default or error handling
}

// set/get s and t wrap modes
void TextureManager::SetTextureWrapS(int id, GLenum mode) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.wrapModeS = mode;
        glBindTexture(GL_TEXTURE_2D, it->second.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mode);
    } else {
        std::cerr << "TextureManager::SetTextureWrapS - Texture ID not found: " << id << std::endl;
    }
}

void TextureManager::SetTextureWrapT(int id, GLenum mode) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        it->second.wrapModeT = mode;
        glBindTexture(GL_TEXTURE_2D, it->second.id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mode);
    } else {
        std::cerr << "TextureManager::SetTextureWrapT - Texture ID not found: " << id << std::endl;
    }
}

GLenum TextureManager::GetTextureWrapS(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.wrapModeS;
    }
    std::cerr << "TextureManager::GetTextureWrapS - Texture ID not found: " << id << std::endl;
    return GL_REPEAT; // Default or error handling
}

GLenum TextureManager::GetTextureWrapT(int id) const {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second.wrapModeT;
    }
    std::cerr << "TextureManager::GetTextureWrapT - Texture ID not found: " << id << std::endl;
    return GL_REPEAT; // Default or error handling
}

} // namespace RavenEngine