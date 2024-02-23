// physicsengine.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <memory>
#include <vector>
// Third party includes

// Raven includes
#include "RigidBody.h"
#include "CollisionManager.h"

namespace RavenEngine {

class PhysicsEngine {
public:
    PhysicsEngine() : collisionManager(&CollisionManager::GetInstance()) {}
    void Update(float deltaTime);
    void AddRigidBody(std::shared_ptr<RigidBody> body);
    void RemoveRigidBody(std::shared_ptr<RigidBody> body);

    void SetGravity(const glm::vec2& gravity) {
        this->gravity = gravity;
    }

    void SetGravityEnabled(bool enabled) {
        this->gravityEnabled = enabled;
    }


private:
    void Integrate(std::shared_ptr<RigidBody> body, float deltaTime);
    void HandleCollisions();
    bool IsColliding(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2);
    void HandleCollision(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2);

    std::vector<std::shared_ptr<RigidBody>> rigidBodies;
    CollisionManager* collisionManager; // Declare a pointer to the CollisionManager singleton

    glm::vec2 gravity;
    bool gravityEnabled;

};

} // namespace RavenEngine