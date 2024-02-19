// rigidbodypanel.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes

// Raven includes
#include "RigidBodyPanel.h"

namespace RavenEngine {

RigidBodyPanel::RigidBodyPanel(std::shared_ptr<RigidBody> rigidBody) : rigidBody(rigidBody) {}

void RigidBodyPanel::Display() {
    if (!rigidBody) return;

    float mass = rigidBody->GetMass();
    if (ImGui::DragFloat("Mass", &mass, 0.1f, 0.01f, 1000.0f)) {
        rigidBody->SetMass(mass);
        std::cout << "Mass: " << mass << std::endl;
    }

    glm::vec2 velocity = rigidBody->GetVelocity();
    if (ImGui::DragFloat2("Velocity", &velocity[0], 0.1f, -1000.0f, 1000.0f)) {
        rigidBody->SetVelocity(velocity);
        std::cout << "Velocity: (" << velocity.x << ", " << velocity.y << ")" << std::endl;
    }

    float angularVelocity = rigidBody->GetAngularVelocity();
    if (ImGui::DragFloat("Angular Velocity", &angularVelocity, 0.1f, -1000.0f, 1000.0f)) {
        rigidBody->SetAngularVelocity(angularVelocity);
        std::cout << "Angular Velocity: " << angularVelocity << std::endl;
    }

    float friction = rigidBody->GetFriction();
    if (ImGui::DragFloat("Friction", &friction, 0.005f, 0.0f, 1.0f)) {
        rigidBody->SetFriction(friction);
        std::cout << "Friction: " << friction << std::endl;
    }

    float restitution = rigidBody->GetRestitution();
    if (ImGui::DragFloat("Restitution", &restitution, 0.005f, 0.0f, 1.0f)) {
        rigidBody->SetRestitution(restitution);
        std::cout << "Restitution: " << restitution << std::endl;
    }
}

} // namespace RavenEngine
