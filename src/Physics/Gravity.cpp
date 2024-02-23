// gravity.cpp
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes

// Raven includes
#include "Gravity.h"

namespace RavenEngine {
Gravity::Gravity() {
    // Initialize with default Earth gravity or load from settings
}

void Gravity::ApplyGravity(RavenEngine::RigidBody& rigidBody, float deltaTime) {
    double currentGravity = gravityManager.GetCurrentGravity();
    // Apply gravity to the rigidBody. This is pseudocode and will depend on your physics engine
    rigidBody.SetVelocity(rigidBody.GetVelocity() - glm::vec2(0, static_cast<float>(currentGravity * deltaTime))); // Assuming downward gravity
}

} // namespace RavenEngine