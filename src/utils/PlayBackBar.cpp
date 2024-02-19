// playbackbar.cpp
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes
#include <imgui.h>

// Raven includes
#include "PlaybackBar.h"
#include "../../include/core/GameStateManager.h"

void RavenEngine::PlaybackBar::Draw() {
    if (ImGui::Button("Start")) {
        GameStateManager::GetInstance().SetState(GameState::Running);
    }

    ImGui::SameLine();

    if (ImGui::Button("Pause")) {
        GameStateManager::GetInstance().SetState(GameState::Paused);
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop")) {
        GameStateManager::GetInstance().SetState(GameState::Stopped);
    }
}