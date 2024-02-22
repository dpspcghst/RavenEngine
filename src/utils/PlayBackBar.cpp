// playbackbar.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes
#include <imgui.h>

// Raven includes
#include "PlaybackBar.h"
#include "../../include/core/GameStateManager.h"

void RavenEngine::PlaybackBar::Draw() {
    if (ImGui::Button("Start")) {
        GameStateManager::GetInstance().SetState(GameState::Running);
        std::cout << "PLAYBACKBAR::DRAW START PING!" << std::endl;
    }

    ImGui::SameLine();

    if (ImGui::Button("Pause")) {
        GameStateManager::GetInstance().SetState(GameState::Paused);
        std::cout << "PLAYBACKBAR::DRAW PAUSE PING!" << std::endl;
    }

    ImGui::SameLine();

    if (ImGui::Button("Stop")) {
        GameStateManager::GetInstance().SetState(GameState::Stopped);
        std::cout << "PLAYBACKBAR::DRAW STOP PING!" << std::endl;
    }
}