// texturemanagerpanel.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <vector>
#include <algorithm>
#include <iostream>
// Third-party includes
#include <imgui.h>
// Raven includes
#include "TextureManagerPanel.h"
#include "TextureFileDialog.h"
#include "TextureManager.h"
#include "TexturePreview.h"

namespace RavenEngine {

TextureManagerPanel::TextureManagerPanel(TextureManager& textureManager, std::function<void(int)> onTextureLoadedCallback)
    : textureManager(textureManager), onTextureLoadedCallback(std::move(onTextureLoadedCallback)) {
}

void TextureManagerPanel::Draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(15, 15));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));

    ImGui::Begin("Texture Manager");
    DrawLoadTextureButton();
    ImGui::SameLine();
    DrawTextureList();
    DrawDeleteButton();
    ImGui::End();

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void TextureManagerPanel::DrawLoadTextureButton() {
    if (ImGui::Button("Load Texture")) {
        LoadNewTexture();
    }
}
void TextureManagerPanel::DrawTextureList() {
    const auto& textures = textureManager.GetTextures();
    const int numColumns = 4;
    int i = 0;

    if (ImGui::BeginTable("Textures", numColumns, ImGuiTableFlags_Borders)) {
        for (const auto& texturePair : textures) {
            if (i % numColumns == 0) ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(i % numColumns);

            DrawTextureSelectable(texturePair.first, texturePair.second.filepath);
            i++;
        }
        ImGui::EndTable();
    }
}

void TextureManagerPanel::DrawTextureSelectable(int textureID, const std::string &filepath) {
    ImGui::PushID(textureID);
    bool isSelected = std::find(selectedTextures.begin(), selectedTextures.end(), textureID) != selectedTextures.end();
    if (ImGui::Selectable("##Selectable", isSelected, ImGuiSelectableFlags_AllowDoubleClick)) {
        HandleTextureSelection(textureID);
    }

    ImGui::SameLine();
    DrawTexturePreview(textureID, filepath);
    ImGui::PopID();
}

void TextureManagerPanel::DrawTexturePreview(int textureID, const std::string &filepath) {
    TextureInfo textureInfo = textureManager.GetTexture(textureID);
    std::string filename = textureInfo.filename;

    //std::cout << "Drawing texture preview for texture with ID " << textureID << ", filepath " << filepath << ", and filename " << filename << std::endl;

    if (texturePreviews.count(textureID) == 0) {
        std::cout << "Creating new TexturePreview for texture with ID " << textureID << std::endl;
        texturePreviews[textureID] = std::make_unique<TexturePreview>(filepath);
    }

    texturePreviews[textureID]->DrawThumbnail(64.0f);
    ImGui::SameLine();
    ImGui::Text("%s (%s)", filename.c_str(), filepath.c_str());
}

void TextureManagerPanel::HandleTextureSelection(int textureID) {
    if (!ImGui::GetIO().KeyCtrl) {
        selectedTextures.clear();
    }
    auto it = std::find(selectedTextures.begin(), selectedTextures.end(), textureID);
    if (it == selectedTextures.end()) {
        selectedTextures.push_back(textureID);
    } else {
        selectedTextures.erase(it);
    }
}

void TextureManagerPanel::DrawDeleteButton() {
    if (!selectedTextures.empty() && ImGui::Button("Delete Selected Textures")) {
        for (int id : selectedTextures) {
            textureManager.UnloadTexture(id);
            texturePreviews.erase(id);
        }
        selectedTextures.clear();
    }
}

void TextureManagerPanel::LoadNewTexture() {
    GLFWwindow* currentWindow = glfwGetCurrentContext(); // Make sure you have access to this function
    std::string filepath = TextureFileDialog::OpenTextureDialog(currentWindow);
    if (!filepath.empty()) {
        std::cout << "TEXTUREMANAGERPANEL::LOADNEWTEXTURE Loading texture from file: " << filepath << std::endl;
        int newTextureId = textureManager.LoadTexture(filepath, true); // Assuming true for mipmaps
        std::cout << "TEXTUREMANAGERPANEL::LOADNEWTEXTURE Assigned Texture ID: " << newTextureId << " to file: " << filepath << std::endl;
        onTextureLoadedCallback(newTextureId);
    }
}

} // namespace RavenEngine