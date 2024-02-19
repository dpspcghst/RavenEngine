// collisionpanel.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <memory> // For std::shared_ptr
// Third party includes

// Raven includes
#include "../Renderer/Shapes/Shape2d/Shape2d.h" 

namespace RavenEngine {

class CollisionPanel {
public:
    CollisionPanel() = default;
    ~CollisionPanel() = default;

    CollisionPanel(const CollisionPanel&) = delete;
    CollisionPanel& operator=(const CollisionPanel&) = delete;
    CollisionPanel(CollisionPanel&&) = delete;
    CollisionPanel& operator=(CollisionPanel&&) = delete;

    void DisplaySettings(std::shared_ptr<Shape2D> shape);

private:
    void DisplayBodyTypeOptions(std::shared_ptr<Shape2D> shape);
    void DisplayCollisionToggle(std::shared_ptr<Shape2D> shape);
    float collisionFadeTimer = 0.0f;
};

} // namespace RavenEngine