// gameloop.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes

// Raven includes
#include "GameStateManager.h"

namespace RavenEngine {

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    // Initializes the game loop
    void Initialize();

    // Starts the game loop
    void Start();

    // Stops the game loop
    void Stop();

private:
    // The main update function called every frame
    void Update();

    // Renders the game
    void Render();

    bool isRunning;
};

} // namespace RavenEngine