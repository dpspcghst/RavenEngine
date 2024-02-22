// gameloop.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
#include <chrono>
// Third party includes

// Raven includes
#include "GameLoop.h"
#include "../Physics/PhysicsEngine.h"
#include "../Renderer/Renderer.h"
#include "../Scene/SceneManager.h"

namespace RavenEngine {

GameLoop::GameLoop() : isRunning(false) {}

GameLoop::~GameLoop() {}

void GameLoop::Initialize() {
    renderer->InitializeRenderer();
}

void GameLoop::Start() {
    std::cout << "GAMELOOP::START START PING!" << std::endl;
    GameStateManager::GetInstance().SetState(GameState::Running);

    using Clock = std::chrono::high_resolution_clock;
    auto previousTime = Clock::now();
    double lag = 0.0;
    const double MS_PER_UPDATE = 16.6667; // Approximately 60 updates per second

    while (GameStateManager::GetInstance().GetState() == GameState::Running) { // Check the state of the GameStateManager
        auto currentTime = Clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previousTime).count();
        previousTime = currentTime;
        lag += elapsedTime;

        // Process input here

        while (lag >= MS_PER_UPDATE) {
            float deltaTime = static_cast<float>(elapsedTime) / 1000.0f; // Convert milliseconds to seconds
            Update(deltaTime);
            lag -= MS_PER_UPDATE;
        }

        Render();

        // Check game state
        if (GameStateManager::GetInstance().GetState() == GameState::Stopped) {
            break; // Exit the loop if the game state is Stopped
        }
    }
}

void GameLoop::Stop() {
    GameStateManager::GetInstance().SetState(GameState::Stopped);
    std::cout << "GAMELOOP::STOP STOP PING!" << std::endl;
    isRunning = false;
}

void GameLoop::Update(float deltaTime) {
    std::cout << "GAMELOOP::UPDATE Updating..." << std::endl;
    if (GameStateManager::GetInstance().GetState() != GameState::Running) {
        return;
    }
    sceneManager.Update(deltaTime); // Update the scene
    physicsEngine.Update(deltaTime);  // Update the physics engine
}

void GameLoop::Render() {
    renderer->StartFrame(); // Clear the screen
    std::cout << "Renderer started frame" << std::endl;

    if (auto rootNodePtr = sceneManager.GetRootNodePtr(); rootNodePtr) { // Check if the root node is available
        std::cout << "Rendering scene" << std::endl;
        renderer->RenderScene(*rootNodePtr); // Render the scene
    } else { // If the root node is not available, print an error message
        std::cerr << "Error: Root node is not available for rendering.\n";
    }

    if (GameStateManager::GetInstance().GetState() == GameState::Paused) {
        std::cout << "GameState: Paused" << std::endl;
        // Render paused screen or message
        renderer->RenderPausedScreen();
    }

    renderer->FinishFrame(); // Swap buffers
}

} // namespace RavenEngine
