// texturemanager.h
// #####################
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

// #include section
// #####################
// Standard library includes
#include <string>
#include <unordered_map>
// Third-party includes
#include <glad/glad.h>
// Raven includes

namespace RavenEngine {

struct TextureInfo {
    GLuint id;
    float alpha;
    // Add more parameters here as needed
};

class TextureManager {
public:
    static TextureManager& GetInstance(); // Get instance of TextureManager
    TextureManager(TextureManager const&) = delete; // Don't allow copying
    void operator=(TextureManager const&)  = delete; // Don't allow assignment
    
    int LoadTexture(std::string filename, bool generateMipMaps); // Load a texture
    bool UnloadTexture(int id); // Unload a texture

    TextureInfo GetTexture(int id) const;
    std::unordered_map<int, TextureInfo> GetTextures() { return textures; } // Get all textures

    float GetTextureAlpha(int id) const;
    bool SetTextureAlpha(int id, float alpha);

    bool HasTexture(int id) const;

    int GetTextureId(std::string textureName);

private:
    TextureManager(); // Constructor is private
    ~TextureManager(); // Destructor

    std::unordered_map<int, TextureInfo> textures; // Map of textures
    std::unordered_map<int, std::string> idToName;
    int nextId = 1;
};

} // namespace RavenEngine

#endif // TEXTURE_MANAGER_H