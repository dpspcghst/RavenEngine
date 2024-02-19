// physicsengine.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes

// Raven includes
#include "PhysicsEngine.h"
#include "CollisionManager.h"

namespace RavenEngine {

void PhysicsEngine::Update(float deltaTime) {
    std::cout << "PHYSICSENGINE::UPDATE Updating physics engine..." << std::endl;

    // Update physics for all rigid bodies
    for (auto& body : rigidBodies) {
        Integrate(body, deltaTime);
    }

    // Handle any collisions
    HandleCollisions();
}

void PhysicsEngine::AddRigidBody(std::shared_ptr<RigidBody> body) {
    // Add the given rigid body to the list
    rigidBodies.push_back(body);
}

void PhysicsEngine::RemoveRigidBody(std::shared_ptr<RigidBody> body) {
    // Remove the given rigid body from the list
    rigidBodies.erase(std::remove(rigidBodies.begin(), rigidBodies.end(), body), rigidBodies.end());
}

void PhysicsEngine::Integrate(std::shared_ptr<RigidBody> body, float deltaTime) {
    // Update the state of the rigid body based on its current velocity and the elapsed time
    body->SetPosition(body->GetPosition() + body->GetVelocity() * deltaTime);
    body->SetVelocity(body->GetVelocity() + body->GetAcceleration() * deltaTime);

    std::cout << "PHYSICSENGINE::INTEGRATE Integrating body at address: " << body.get() << std::endl;
    std::cout << "Position: (" << body->GetPosition().x << ", " << body->GetPosition().y << ")" << std::endl;
    std::cout << "Velocity: (" << body->GetVelocity().x << ", " << body->GetVelocity().y << ")" << std::endl;
}

void PhysicsEngine::HandleCollision(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {
    std::cout << "PHYSICSENGINE::HANDLECOLLISION Handling collision between bodies at addresses: " << body1.get() << " and " << body2.get() << std::endl;
    // Calculate the direction of the collision
    glm::vec2 collisionNormal = glm::normalize(body1->GetPosition() - body2->GetPosition());

    // Calculate the relative velocity
    glm::vec2 relativeVelocity = body1->GetVelocity() - body2->GetVelocity();

    // Calculate the velocity along the normal
    float velocityAlongNormal = glm::dot(relativeVelocity, collisionNormal);

    // Do nothing if velocities are separating
    if (velocityAlongNormal > 0) {
        return;
    }

    // Calculate the restitution (bounciness)
    float restitution = std::min(body1->GetRestitution(), body2->GetRestitution());

    // Calculate the impulse scalar
    float impulseScalar = -(1 + restitution) * velocityAlongNormal;
    impulseScalar /= 1.0f / body1->GetMass() + 1.0f / body2->GetMass();

    // Apply impulse
    glm::vec2 impulse = impulseScalar * collisionNormal;
    body1->SetVelocity(body1->GetVelocity() + (1.0f / body1->GetMass()) * impulse);
    body2->SetVelocity(body2->GetVelocity() - (1.0f / body2->GetMass()) * impulse);
}

bool PhysicsEngine::IsColliding(std::shared_ptr<RigidBody> body1, std::shared_ptr<RigidBody> body2) {
    std::cout << "PHYSICSENGINE::ISCOLLIDING Checking for collision between bodies at addresses: " << body1.get() << " and " << body2.get() << std::endl;
    return false;
}

void RavenEngine::PhysicsEngine::HandleCollisions() {
    std::cout << "PHYSICSENGINE::HANDLECOLLISIONS Handling collisions..." << std::endl;
    // Loop over all pairs of bodies and check for collisions
    for (auto& body1 : rigidBodies) {
        for (auto& body2 : rigidBodies) {
            if (body1 != body2 && IsColliding(body1, body2)) {
                HandleCollision(body1, body2);
            }
        }
    }
}

} // namespace RavenEngine