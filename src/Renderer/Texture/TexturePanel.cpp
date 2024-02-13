// TexturePanel.cpp

// #include section
// #####################
// Standard library includes

// Third-party includes
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>

// Raven includes
#include "TexturePanel.h"
#include "TextureManager.h"
#include "TexturePreview.h"
#include "TextureFileDialog.h" // Include the TextureFileDialog header

namespace RavenEngine {

TexturePanel::TexturePanel(TextureManager& textureManager, std::function<void(int)> onTextureLoadedCallback)
    : textureManager(textureManager), onTextureLoadedCallback(onTextureLoadedCallback) {
    // Initialization code if needed
}

void TexturePanel::Draw() {
    // Load new texture
    if (ImGui::Button("Load Texture")) {
        std::string filepath = OpenTextureFileDialog();
        if (!filepath.empty()) {
            // Unload the old texture
            if (selectedTexture != -1) {
                textureManager.UnloadTexture(selectedTexture);
                texturePreviews.erase(selectedTexture);
            }

            // Load the new texture
            int newTextureId = textureManager.LoadTexture(filepath, true); // Assuming ID is filepath for simplicity

            // Create a TexturePreview for the new texture
            texturePreviews[newTextureId] = std::make_unique<RavenEngine::TexturePreview>(filepath);

            // Update the selected texture
            selectedTexture = newTextureId;

            // Call the callback function
            onTextureLoadedCallback(selectedTexture);
        }
    }

    // Show the file path of the selected texture
    if (selectedTexture != -1) {
        ImGui::Text("Selected Texture: %d", selectedTexture);

        // Add a slider to control the alpha of the texture
        float alpha = textureManager.GetTextureAlpha(selectedTexture); // Get the current alpha of the texture
        if (ImGui::SliderFloat("Alpha", &alpha, 0.0f, 1.0f)) { // Slider from 0 (transparent) to 1 (opaque)
            textureManager.SetTextureAlpha(selectedTexture, alpha); // Set the new alpha of the texture
        }
    }

    // List all textures
    for (const auto& texturePair : textureManager.GetTextures()) { // Iterate through all textures
        int textureID = texturePair.first;
        ImGui::Text("%d", textureID); // Texture ID

        // Draw the texture thumbnail
        if (texturePreviews.count(textureID) > 0) {
            if (ImGui::ImageButton((ImTextureID)(intptr_t)texturePair.second.id, ImVec2(64, 64))) { // if texture is clicked
                selectedTexture = textureID; // Update the selected texture
            }
        }

        ImGui::SameLine(); // Keep listing textures in the same line
    }
    ImGui::NewLine(); // Ensure next UI element is on a new line after the texture list
}

std::string TexturePanel::OpenTextureFileDialog() { // Open file dialog to select a texture file
    // Use the TextureFileDialog to open a texture file dialog
    return TextureFileDialog::OpenTextureDialog(glfwGetCurrentContext());
}

}   // namespace RavenEngine