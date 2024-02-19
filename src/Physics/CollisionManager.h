// collisionmanager.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <vector>
// Third party includes
#include <glm/vec2.hpp>
// Raven includes
#include "../Renderer/Shapes/Shape2d/Shape2d.h" 

namespace RavenEngine {

class CollisionManager {
public:
    static CollisionManager& GetInstance();

    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;

    void AddShape(Shape2D* shape);
    void RemoveShape(Shape2D* shape);
    bool CheckCollision(Shape2D* a, Shape2D* b);
    void CheckCollisions();
    void CheckSATCollisions();

    // Add the new method declaration here
    bool CheckCollisionForShape(Shape2D* shape);

private:
    CollisionManager() {} // Constructor is private
    ~CollisionManager() {}

    std::vector<Shape2D*> shapes; // Store pointers to Shape2D objects

    
    bool CheckSATCollision(Shape2D* a, Shape2D* b);
    bool Overlap(const Shape2D::Projection& projA, const Shape2D::Projection& projB);
    std::vector<glm::vec2> GetAxes(Shape2D* a, Shape2D* b);
};

} // namespace RavenEngine