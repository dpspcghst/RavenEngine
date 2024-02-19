// rigidbody.cpp
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes

// Raven includes
#include "RigidBody.h"

namespace RavenEngine {

RigidBody::RigidBody() 
    : mass(1.0f), 
      velocity(glm::vec2(0.0f)), 
      accumulatedForce(glm::vec2(0.0f)), 
      angularVelocity(0.0f), 
      angularAcceleration(0.0f), 
      momentOfInertia(1.0f), 
      friction(0.0f), 
      restitution(0.0f) {}

void RigidBody::Update(float deltaTime) {
    Integrate(deltaTime);
}

void RigidBody::SetMass(float newMass) {
    mass = newMass;
}

void RigidBody::SetVelocity(const glm::vec2& newVelocity) {
    velocity = newVelocity;
}

void RigidBody::ApplyForce(const glm::vec2& force) {
    accumulatedForce += force;
}

void RigidBody::SetAngularVelocity(float newAngularVelocity) {
    angularVelocity = newAngularVelocity;
}

void RigidBody::ApplyTorque(float torque) {
    angularAcceleration += torque / momentOfInertia;
}

void RigidBody::SetFriction(float newFriction) {
    friction = newFriction;
}

void RigidBody::SetRestitution(float newRestitution) {
    restitution = newRestitution;
}

float RigidBody::GetMass() const {
    return mass;
}

glm::vec2 RigidBody::GetVelocity() const {
    return velocity;
}

float RigidBody::GetAngularVelocity() const {
    return angularVelocity;
}

float RigidBody::GetFriction() const {
    return friction;
}

float RigidBody::GetRestitution() const {
    return restitution;
}

void RigidBody::SetPosition(const glm::vec2& newPosition) {
    position = newPosition;
}

glm::vec2 RigidBody::GetPosition() const {
    return position;
}

glm::vec2 RigidBody::GetAcceleration() const {
    return accumulatedForce / mass;
}

void RigidBody::Integrate(float deltaTime) {
    if (mass <= 0.0f) return;

    // Update velocity based on accumulated forces
    glm::vec2 acceleration = accumulatedForce / mass;
    velocity += acceleration * deltaTime;

    // Update position based on velocity
    position += velocity * deltaTime;

    // Update angular velocity based on angular acceleration
    angularVelocity += angularAcceleration * deltaTime;

    // Reset accumulated force and angular acceleration
    accumulatedForce = glm::vec2(0.0f);
    angularAcceleration = 0.0f;
}

} // namespace RavenEngine