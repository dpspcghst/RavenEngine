// gameloop.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <chrono>
// Third party includes

// Raven includes
#include "GameLoop.h"

namespace RavenEngine {

GameLoop::GameLoop() : isRunning(false) {}

GameLoop::~GameLoop() {}

void GameLoop::Initialize() {
    // Initialization code here (e.g., load resources)
}

void GameLoop::Start() {
    isRunning = true;
    GameStateManager::GetInstance().SetState(GameState::Running);

    using Clock = std::chrono::high_resolution_clock;
    auto previousTime = Clock::now();
    double lag = 0.0;
    const double MS_PER_UPDATE = 16.6667; // Approximately 60 updates per second

    while (isRunning) {
        auto currentTime = Clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
        previousTime = currentTime;
        lag += elapsedTime;

        // Process input here

        while (lag >= MS_PER_UPDATE) {
            Update();
            lag -= MS_PER_UPDATE;
        }

        Render();

        // Check game state
        if (GameStateManager::GetInstance().GetState() == GameState::Stopped) {
            isRunning = false;
        }
    }
}

void GameLoop::Stop() {
    GameStateManager::GetInstance().SetState(GameState::Stopped);
}

void GameLoop::Update() {
    // Update game logic here
}

void GameLoop::Render() {
    // Rendering code here
}

} // namespace RavenEngine
