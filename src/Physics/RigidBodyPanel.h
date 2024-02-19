// rigidbodypanel.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <memory>
// Third party includes
#include <imgui.h>
// Raven includes
#include "RigidBody.h"

namespace RavenEngine {

class RigidBodyPanel {
public:
    explicit RigidBodyPanel(std::shared_ptr<RigidBody> rigidBody);

    void Display();

private:
    std::shared_ptr<RigidBody> rigidBody;
};

} // namespace RavenEngine
