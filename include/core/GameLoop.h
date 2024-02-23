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
#include "../../src/Physics/PhysicsEngine.h"
#include "../../src/Renderer/Renderer.h"
#include "../../src/Scene/SceneManager.h"

namespace RavenEngine {

class GameLoop {
public:
    GameLoop();
    ~GameLoop();

    void Initialize();
    void Start();
    void Stop();
    void Update(float deltaTime);
    void Render();

private:
    PhysicsEngine physicsEngine;
    Renderer* renderer;
    SceneManager sceneManager;
    

    bool isRunning;
};

} // namespace RavenEngine