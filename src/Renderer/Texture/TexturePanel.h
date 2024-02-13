// texturepanel.h
// #####################
#ifndef TEXTURE_PANEL_H
#define TEXTURE_PANEL_H

// #include section
// #####################
// Standard library includes
#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

// Third-party includes

// Raven includes
#include "TextureManager.h"
#include "TexturePreview.h"

namespace RavenEngine {
    
class TexturePanel {
public:
    // Constructor takes a reference to the TextureManager to interact with it
    // and a callback function to be called when a new texture is loaded
    TexturePanel(TextureManager& textureManager, std::function<void(int)> onTextureLoadedCallback);

    // Render the texture panel UI
    void Draw();

private:
    TextureManager& textureManager; // Reference to the TextureManager to manage textures
    std::function<void(int)> onTextureLoadedCallback; // Callback function to be called when a new texture is loaded

    std::string OpenTextureFileDialog(); // Open file dialog to select a texture file
    int selectedTexture; // ID of the selected texture
    std::unordered_map<int, std::unique_ptr<RavenEngine::TexturePreview>> texturePreviews;
};

}   // namespace RavenEngine
#endif // TEXTURE_PANEL_H