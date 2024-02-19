// texturemanager.h
// #####################
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
// #####################
// #include section
// #####################
// Standard library includes
#include <string>
#include <unordered_map>
#include <vector>
// Third-party includes
#include <glad/glad.h>
#include <glm/glm.hpp>
// Raven includes

namespace RavenEngine {

struct TextureInfo {
    GLuint id;
    std::string filepath; // File path of the texture
    std::string filename;
    //std::string textureFriendlyName;
    float alpha;
    GLenum filteringMode; // Filtering mode per texture
    GLenum wrapModeS;     // Wrap mode S per texture
    GLenum wrapModeT;     // Wrap mode T per texture
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    glm::vec2 position = glm::vec2(0.0f, 0.0f);
    float rotation = 0.0f;

    // Constructor with default values for new fields
    TextureInfo() : id(0), alpha(1.0f), filteringMode(GL_LINEAR), wrapModeS(GL_REPEAT), wrapModeT(GL_REPEAT) {}
};

class TextureManager {
public:
    static TextureManager& GetInstance();
    TextureManager(TextureManager const&) = delete;
    void operator=(TextureManager const&) = delete;
    
    int LoadTexture(std::string filename, bool generateMipMaps);

    void BindTexture(int id);
    void UnbindTexture();

    bool UnloadTexture(int id);

    TextureInfo GetTexture(int id) const;
    const std::unordered_map<int, TextureInfo>& GetTextures() const { return textures; }

    bool HasTexture(int id) const;
    int GetTextureId(std::string textureName);

    // Texture filtering mode
    void SetTextureFilteringMode(int id, GLenum mode);
    GLenum GetTextureFilteringMode(int id) const;

    // Texture wrap mode
    void SetTextureWrapS(int id, GLenum mode);
    void SetTextureWrapT(int id, GLenum mode);
    GLenum GetTextureWrapS(int id) const;
    GLenum GetTextureWrapT(int id) const;

    // Texture alpha
    float GetTextureAlpha(int id) const;
    bool SetTextureAlpha(int id, float alpha);

    // Texture transformations
    void SetTextureScale(int id, float scaleX, float scaleY);
    float GetTextureScaleX(int id) const;
    float GetTextureScaleY(int id) const;
    // Set the position of the texture
    void SetTexturePosition(int id, glm::vec2 position);
    glm::vec2 GetTexturePosition(int id) const;
    // Set the rotation of the texture
    void SetTextureRotation(int id, float rotation);
    float GetTextureRotation(int id) const;

    std::vector<std::string> GetLoadedTextureFiles() const; // Get file paths of all loaded textures
    std::vector<int> GetLoadedTextureIds() const; // Get IDs of all loaded textures

private:
    TextureManager();
    ~TextureManager();

    GLuint GenerateTexture(unsigned char* data, int width, int height, int nrChannels, bool generateMipMaps);

    std::unordered_map<int, TextureInfo> textures;
    std::unordered_map<int, std::string> idToName;
    int nextId = 1;
};

} // namespace RavenEngine

#endif // TEXTURE_MANAGER_H