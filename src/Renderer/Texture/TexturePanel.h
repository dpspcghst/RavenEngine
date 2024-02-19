// texturepanel.h
// #####################
#ifndef TEXTURE_PANEL_H
#define TEXTURE_PANEL_H
// #####################
// #include section
// #####################
// Standard library includes
#include <string>
#include <functional>
// Third-party includes

// Raven includes
#include "TexturePreview.h"
#include "TextureManager.h"

namespace RavenEngine {

class TexturePanel {
public:
    // Constructor to initialize the TexturePanel with a reference to TextureManager and a callback function
    TexturePanel(TextureManager& textureManager, std::function<void(int)> onTextureLoadedCallback);

    // Main draw function for the TexturePanel
    void Draw();
    bool IsTextureEnabled = false; // New: Boolean to indicate if a texture is enabled
private:
    TextureManager& textureManager; // Reference to the TextureManager to manage textures
    std::unique_ptr<TexturePreview> texturePreview;

    std::function<void(int)> onTextureLoadedCallback; // Callback function to be called when a new texture is loaded
    int selectedTexture = -1; // ID of the currently selected texture, initialized to -1 to indicate no selection

    // Private member functions to modularize the UI drawing process
    void DisplaySelectedTextureProperties(); // Displays properties of the selected texture and allows editing
    void DisplayFilteringModeCombo(); // Displays and allows editing of the texture filtering mode
    void DisplayTextureWrapModeCombo(const char* label, int textureID, bool isWrapS); // Displays and allows editing of texture wrap modes
    void DisplayAlphaSlider(); // Displays and allows editing of the alpha value of the texture
    void DisplayTextureSelectionCombo(); // New: Displays and allows selection of a texture from a combo box
    void DisplayTextureTransformations();

    // Utility functions
    void LoadNewTexture(); // Handles the loading of a new texture
    std::string OpenTextureFileDialog(); // Opens a dialog to select a texture file
};

} // namespace RavenEngine

#endif // TEXTURE_PANEL_H
