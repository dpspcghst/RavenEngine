// texturemanagerpanel.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
// Third-party includes

// Raven includes
#include "TextureManager.h"
#include "TexturePreview.h" 

namespace RavenEngine {

class TextureManagerPanel {
public:
    TextureManagerPanel(TextureManager& textureManager, std::function<void(int)> onTextureLoadedCallback);
    
    void Draw(); // Draws the texture manager panel UI

private:
    TextureManager& textureManager; // Reference to the TextureManager instance
    std::function<void(int)> onTextureLoadedCallback; // Callback function to handle new texture load
    std::unordered_map<int, std::unique_ptr<TexturePreview>> texturePreviews; // Stores texture previews for efficiency
    std::vector<int> selectedTextures; // Tracks selected textures for operations like delete

    // UI component draw functions
    void DrawLoadTextureButton(); // Draws the button to load a new texture
    void DrawTextureList(); // Draws the list of textures with previews
    void DrawTextureItem(const std::pair<int, TextureInfo>& texturePair); // Draws an individual texture item in the list
    void DrawTexturePreview(int textureID, const std::string& filepath); // Draws a preview for a texture
    void HandleTextureSelection(int textureID); // Handles selection logic for textures
    void DrawSelectedTextures(); // Displays selected textures
    void DrawDeleteButton(); // Draws the button to delete selected textures
    void DrawTextureSelectable(int textureID, const std::string& filepath); // Draws a selectable texture item

    void LoadNewTexture(); // Loads a new texture into the manager
};

} // namespace RavenEngine