// TexturePanel.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
#include <vector>
// Third-party includes
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
// Raven includes
#include "TexturePanel.h"
#include "TextureManager.h"
#include "TexturePreview.h"
#include "TextureFileDialog.h" // Include the TextureFileDialog header
#include "../Shaders/ShaderManager.h"

namespace RavenEngine {

TexturePanel::TexturePanel(TextureManager& textureManager, std::function<void(int)> onTextureLoadedCallback)
        : textureManager(textureManager), 
            onTextureLoadedCallback(onTextureLoadedCallback), 
            IsTextureEnabled(false) {
        // constructor implementation
}

std::string TexturePanel::OpenTextureFileDialog() {
    return TextureFileDialog::OpenTextureDialog(glfwGetCurrentContext());
}

std::string GetFilenameFromPath(const std::string& filepath) {
    size_t pos = filepath.find_last_of("/\\");
    return (pos != std::string::npos) ? filepath.substr(pos + 1) : filepath;
}

void TexturePanel::DisplaySelectedTextureProperties() {
    if (selectedTexture != -1 && textureManager.HasTexture(selectedTexture)) {
        ImGui::Text("Properties:");
        ImGui::Separator();
        if (ImGui::CollapsingHeader("Filtering Mode")) {
            DisplayFilteringModeCombo();
        }
        ImGui::Separator();
        if (ImGui::CollapsingHeader("Wrap Modes")) {
            DisplayTextureWrapModeCombo("Horizontal(S)", selectedTexture, true);
            DisplayTextureWrapModeCombo("Vertical(T)", selectedTexture, false);
        }
        ImGui::Separator();
        if (ImGui::CollapsingHeader("Alpha")) {
            DisplayAlphaSlider();
        }
        ImGui::Separator();
        if (ImGui::CollapsingHeader("Transformations")) {
            DisplayTextureTransformations();
        }
    }
}

void TexturePanel::DisplayTextureSelectionCombo() {
    std::string previewValue = selectedTexture != -1 ? GetFilenameFromPath(textureManager.GetTexture(selectedTexture).filename) : "None";
    if (ImGui::BeginCombo("Select Texture", previewValue.c_str())) {
        const auto& textures = textureManager.GetTextures();
        for (const auto& texturePair : textures) {
            std::string filename = GetFilenameFromPath(texturePair.second.filename); // Extract filename from full path
            ImGui::PushID(texturePair.first);
            bool isSelected = (texturePair.first == selectedTexture);
            if (ImGui::Selectable(filename.c_str(), isSelected)) {
                if (selectedTexture != texturePair.first) {
                    selectedTexture = texturePair.first;
                    // Reload the texture for preview to ensure it matches the selected texture
                    texturePreview = std::make_unique<TexturePreview>(texturePair.second.filename); // Use the full path here
                    onTextureLoadedCallback(selectedTexture);
                }
            }
            if (isSelected) ImGui::SetItemDefaultFocus();
            ImGui::PopID();
        }
        ImGui::EndCombo();
    }
}

void TexturePanel::DisplayFilteringModeCombo() {
    const char* items[] = {"Linear Filtering", "Nearest Filtering"};
    int currentItem = textureManager.GetTextureFilteringMode(selectedTexture) == GL_LINEAR ? 0 : 1;
    if (ImGui::Combo("", &currentItem, items, IM_ARRAYSIZE(items))) {
        GLenum newMode = currentItem == 0 ? GL_LINEAR : GL_NEAREST;
        textureManager.SetTextureFilteringMode(selectedTexture, newMode);
    }
}

void TexturePanel::DisplayAlphaSlider() {
    float alpha = textureManager.GetTextureAlpha(selectedTexture);
    float alphaPercentage = alpha * 100.0f; // Convert alpha (0-1) to percentage (0-100)

    // Using a label for the slider for better UX. Providing an ID for the slider to avoid conflicts.
    if (ImGui::SliderFloat("Alpha##alphaSlider", &alphaPercentage, 0.0f, 100.0f, "%.1f%%")) {
        alpha = alphaPercentage / 100.0f; // Convert back percentage to alpha (0-1)
        textureManager.SetTextureAlpha(selectedTexture, alpha);

        // Update the shader with the new alpha value
        if (auto shaderProgram = ShaderManager::GetInstance().GetShader("defaultShader")) {
            shaderProgram->SetAlpha(alpha);
        }
    }
}

void TexturePanel::DisplayTextureWrapModeCombo(const char* label, int textureID, bool isWrapS) {
    const char* wrapItems[] = { "Repeat", "Clamp to Edge", "Mirrored Repeat", "Clamp to Border" };
    int currentWrapMode = isWrapS ? textureManager.GetTextureWrapS(textureID) : textureManager.GetTextureWrapT(textureID);
    if (ImGui::Combo(label, &currentWrapMode, wrapItems, IM_ARRAYSIZE(wrapItems))) {
        if (isWrapS) {
            textureManager.SetTextureWrapS(textureID, currentWrapMode);
        } else {
            textureManager.SetTextureWrapT(textureID, currentWrapMode);
        }
    }
}

void TexturePanel::LoadNewTexture() {
    std::string filepath = OpenTextureFileDialog();
    if (!filepath.empty()) {
        int newTextureId = textureManager.LoadTexture(filepath, true);
        selectedTexture = newTextureId;
        onTextureLoadedCallback(selectedTexture);
    }
}

void TexturePanel::DisplayTextureTransformations() {

    ImGui::Columns(2, "textureTransformColumn"); // 2 columns

    ImGui::Separator();
    ImGui::Text("Transformation");
    ImGui::NextColumn();
    ImGui::Text("Value");
    ImGui::NextColumn();
    ImGui::Separator();

    float scaleX = textureManager.GetTextureScaleX(selectedTexture);
    float scaleY = textureManager.GetTextureScaleY(selectedTexture);

    ImGui::Text("Scale X");
    ImGui::NextColumn();
    if (ImGui::InputFloat("##Scale X", &scaleX)) {
        textureManager.SetTextureScale(selectedTexture, scaleX, scaleY);
    }
    ImGui::NextColumn();

    ImGui::Text("Scale Y");
    ImGui::NextColumn();
    if (ImGui::InputFloat("##Scale Y", &scaleY)) {
        textureManager.SetTextureScale(selectedTexture, scaleX, scaleY);
    }
    ImGui::NextColumn();

    glm::vec2 position = textureManager.GetTexturePosition(selectedTexture);
    ImGui::Text("Position");
    ImGui::NextColumn();
    if (ImGui::InputFloat2("##Position", glm::value_ptr(position))) {
        textureManager.SetTexturePosition(selectedTexture, position);
    }
    ImGui::NextColumn();

    float rotation = textureManager.GetTextureRotation(selectedTexture);
    ImGui::Text("Rotation");
    ImGui::NextColumn();
    if (ImGui::InputFloat("##Rotation", &rotation)) {
        textureManager.SetTextureRotation(selectedTexture, rotation);
    }
    ImGui::NextColumn();

    ImGui::Columns(1);
    ImGui::Separator();
}

void TexturePanel::Draw() {
    std::vector<std::string> filenames;
    DisplayTextureSelectionCombo();
    if (ImGui::Button("Load Texture")) { // load button
        std::string filepath = OpenTextureFileDialog();
        if (!filepath.empty()) {
            int newTextureId = textureManager.LoadTexture(filepath, true);
            if (newTextureId != -1) {
                selectedTexture = newTextureId;
                texturePreview = std::make_unique<TexturePreview>(filepath);
                onTextureLoadedCallback(selectedTexture);
                IsTextureEnabled = true;
            }
        }
    }
    ImGui::SameLine();
    if (selectedTexture != -1 && textureManager.HasTexture(selectedTexture)) { // Check if the selected texture is valid
        ImGui::SameLine();
        // When toggling the checkbox, directly manipulate the visibility of the preview and the callback
        if (ImGui::Checkbox(IsTextureEnabled ? "Disable Texture" : "Enable Texture", &IsTextureEnabled)) {
            if (!IsTextureEnabled) {
                // If disabling, you might want to do additional logic like notifying other components
                onTextureLoadedCallback(-1); // Optionally notify that texture is disabled if needed
            } else {
                // Ensure re-enabling also refreshes the preview if needed
                onTextureLoadedCallback(selectedTexture);
            }
        }
        // Always display "Preview:"
        ImGui::Text("Preview:");
        // Conditional rendering of the texture preview based on IsTextureEnabled
        if (IsTextureEnabled && texturePreview) { // Only render the preview if the texture is enabled
            texturePreview->DrawThumbnail(120.0f);
            DisplaySelectedTextureProperties();
        } else { // If the texture is disabled, display a message
            ImGui::Text("Texture disabled.");
        }
    } else { // If no texture is selected
        ImGui::Text("No texture selected.");
    }
}

} // namespace RavenEngine