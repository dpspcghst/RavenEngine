// palette.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
#include <algorithm>
#include <random>

// Third party includes

// Raven includes
#include "Palette.h"

namespace RavenEngine {

Palette::Palette() : initialPos(100.0f, 100.0f), paletteTitle("Palette"), closeRequested(false) {
    // Initialize colors with default values or random colors
    for (auto& color : colors) {
        color = ImVec4(rand() / (float) RAND_MAX, rand() / (float) RAND_MAX, rand() / (float) RAND_MAX, 1.0f);
    }
}

Palette::~Palette() {}

void Palette::SetTitle(const std::string& title) {
    paletteTitle = title;
}

void Palette::DrawUI() {
    bool open = true;
    if (ImGui::Begin(paletteTitle.c_str(), &open, ImGuiWindowFlags_None)) {
        DrawColorSquares();

        // Check if the space bar is pressed and the window is focused
        if (ImGui::IsWindowFocused() && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Space))) {
            // Generate new random colors for unlocked colors
            for (int i = 0; i < colors.size(); i++) {
                if (!locked[i]) {
                    colors[i] = ImVec4(rand() / (float) RAND_MAX, rand() / (float) RAND_MAX, rand() / (float) RAND_MAX, 1.0f);
                }
            }
        }
    }
    ImGui::End();
    if (!open) {
        closeRequested = true;
        std::cout << "Closing the palette window\n";
    }
}

void Palette::DrawColorSquares() {
    for (int i = 0; i < colors.size(); i++) {
        ImGui::PushID(i); // Ensure each button has a unique ID
        
        // Color button
        if (ImGui::ColorButton("##Color", colors[i], ImGuiColorEditFlags_NoAlpha, ImVec2(50, 50))) {
            ImGui::OpenPopup("color_picker");
        }
        
        // Color picker popup
        if (ImGui::BeginPopup("color_picker")) {
            if (!locked[i]) {
                ImGui::ColorPicker4("##Picker", (float*)&colors[i], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
            }
            ImGui::EndPopup();
        }
        
        // Right-click context menu
        if (ImGui::BeginPopupContextItem("context")) {
            if (ImGui::MenuItem("Lock")) {
                locked[i] = true;
            }
            if (ImGui::MenuItem("Unlock")) {
                locked[i] = false;
            }
            if (ImGui::MenuItem("Copy")) {
                char hexColor[8];
                sprintf_s(hexColor, sizeof(hexColor), "#%02X%02X%02X", static_cast<int>(colors[i].x * 255), static_cast<int>(colors[i].y * 255), static_cast<int>(colors[i].z * 255));
                ImGui::SetClipboardText(hexColor);
            }
            ImGui::EndPopup();
        }
        
        ImGui::PopID(); // Pop ID
        ImGui::SameLine(); // Display the squares in a row
    }
    ImGui::NewLine(); // Ensures that the next UI elements are below the color squares
}

bool Palette::CloseRequested() const {
    return closeRequested;
}

} // namespace RavenEngine