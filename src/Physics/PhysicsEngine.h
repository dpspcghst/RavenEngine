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

namespace RavenEngine {

class PhysicsEngine {
public:
    void Update(float deltaTime);
    void AddRigidBody(std::shared_ptr<RigidBody> body);
    void RemoveRigidBody(std::shared_ptr<RigidBody> body);

private:
    void Integrate(std::shared_ptr<RigidBody> body, float deltaTime);
    void HandleCollisions();
    bool IsColliding(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2);
    void HandleCollision(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2);

    std::vector<std::shared_ptr<RigidBody>> rigidBodies;
};

} // namespace RavenEngine
