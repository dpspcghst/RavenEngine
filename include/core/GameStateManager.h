// gamestatemanager.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes

// Raven includes

namespace RavenEngine {

enum class GameState {
    Stopped,
    Running,
    Paused
};

class GameStateManager {
public:
    static GameStateManager& GetInstance() {
        static GameStateManager instance;
        return instance;
    }

    GameStateManager(const GameStateManager&) = delete;
    GameStateManager& operator=(const GameStateManager&) = delete;

    // Sets the current game state
    void SetState(GameState newState) {
    currentState = newState;
    std::cout << "GameStateManager::SetState State changed to: ";
    switch (newState) {
        case GameState::Stopped:
            std::cout << "Stopped";
            break;
        case GameState::Running:
            std::cout << "Running";
            break;
        case GameState::Paused:
            std::cout << "Paused";
            break;
    }
    std::cout << std::endl;
}
    // Returns the current game state
    GameState GetState() const {
        std::cout << "GameStateManager::GetState START PING! Current state: ";
        switch (currentState) {
            case GameState::Stopped:
                std::cout << "Stopped";
                break;
            case GameState::Running:
                std::cout << "Running";
                break;
            case GameState::Paused:
                std::cout << "Paused";
                break;
        }
        std::cout << std::endl;
        return currentState;
    }

private:
    GameStateManager() : currentState(GameState::Stopped) {}

    GameState currentState;
};

} // namespace RavenEngine
