// collisionpanel.cpp
// #####################
// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes
#include <imgui.h>
// Raven includes
#include "CollisionManager.h"
#include "CollisionPanel.h"
#include "../Renderer/Shapes/Shape2d/Shape2d.h"

namespace RavenEngine {

void CollisionPanel::DisplaySettings(std::shared_ptr<Shape2D> shape) {
    if (!shape) return;

    if (ImGui::CollapsingHeader("Collision Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
        DisplayCollisionToggle(shape);
        DisplayBodyTypeOptions(shape);
    }

    // Collision detector
    if (ImGui::CollapsingHeader("Collision Detector", ImGuiTreeNodeFlags_DefaultOpen)) {
        bool isColliding = RavenEngine::CollisionManager::GetInstance().CheckCollisionForShape(shape.get());

        // Update the collision fade timer
        if (isColliding) {
            collisionFadeTimer = 1.0f;  // Reset the timer when a collision occurs
        } else if (collisionFadeTimer > 0.0f) {
            collisionFadeTimer -= ImGui::GetIO().DeltaTime;  // Decrease the timer over time
        }

        // Calculate the color based on the collision fade timer
        ImVec4 squareColor = ImVec4(collisionFadeTimer, 1.0f - collisionFadeTimer, 0.0f, 1.0f);
        ImGui::Text("Collision Status:");
        ImGui::SameLine();
        ImGui::ColorButton("##collisionStatus", squareColor, ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoLabel, ImVec2(20, 20));
    }

}

void CollisionPanel::DisplayCollisionToggle(std::shared_ptr<Shape2D> shape) {
    bool collisionEnabled = shape->IsCollisionEnabled();
    if (ImGui::Checkbox("Enable Collision", &collisionEnabled)) {
        shape->SetCollisionEnabled(collisionEnabled);
        std::cout << "Collision Enabled: " << collisionEnabled << std::endl;
    }
}

void CollisionPanel::DisplayBodyTypeOptions(std::shared_ptr<Shape2D> shape) {
    const char* bodyTypes[] = { "Static", "Dynamic", "Kinematic" };
    int currentType = static_cast<int>(shape->GetBodyType());
    if (ImGui::Combo("Body Type", &currentType, bodyTypes, IM_ARRAYSIZE(bodyTypes))) {
        shape->SetBodyType(static_cast<Shape2D::BodyType>(currentType));
    }
}

} // namespace RavenEngine