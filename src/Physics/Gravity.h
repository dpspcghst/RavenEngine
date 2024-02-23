// gravity.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes

// Raven includes
#include "GravityManager.h" // For GravityManager
#include "RigidBody.h" // For RigidBody

namespace RavenEngine {
class Gravity {
public:
    Gravity();

    void ApplyGravity(RigidBody& rigidBody, float deltaTime); // Updated function

private:
    GravityManager gravityManager;
};
} // namespace RavenEngine