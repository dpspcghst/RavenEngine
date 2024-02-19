// rigidbody.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes
#include <glm/vec2.hpp>

// Raven includes
#include "../Renderer/Shapes/Shape.h"
#include "../Renderer/Shapes/Shape2d/Shape2d.h"

namespace RavenEngine {

class RigidBody {
public:
    RigidBody();

    void Update(float deltaTime);

    // Setters
    void SetMass(float mass);
    void SetVelocity(const glm::vec2& velocity);
    void ApplyForce(const glm::vec2& force);
    void SetAngularVelocity(float newAngularVelocity);
    void ApplyTorque(float torque);
    void SetFriction(float newFriction);
    void SetRestitution(float newRestitution);
    void SetPosition(const glm::vec2& position);

    // Getters
    float GetMass() const;
    glm::vec2 GetVelocity() const;
    float GetAngularVelocity() const;
    float GetFriction() const;
    float GetRestitution() const;
    glm::vec2 GetPosition() const;
    glm::vec2 GetAcceleration() const;

    float GetInverseMass() const {
        if (mass == 0.0f) {
            return 0.0f;
        } else {
            return 1.0f / mass;
        }
    }

    std::shared_ptr<Shape> GetShape() const { return shape; }

private:
    float mass;
    glm::vec2 velocity;
    glm::vec2 accumulatedForce;
    float angularVelocity;
    float angularAcceleration;
    float momentOfInertia;
    float friction;
    float restitution;
    glm::vec2 position;
    glm::vec2 acceleration;

    void Integrate(float deltaTime);

    std::shared_ptr<Shape> shape;
};

} // namespace RavenEngine