// gamestatemanager.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

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
    }

    // Returns the current game state
    GameState GetState() const {
        return currentState;
    }

private:
    GameStateManager() : currentState(GameState::Stopped) {}

    GameState currentState;
};

} // namespace RavenEngine
