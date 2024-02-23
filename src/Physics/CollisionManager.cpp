// collisionmanager.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes
#include <glm/glm.hpp>
// Raven includes
#include "CollisionManager.h"
#include "PhysicsEngine.h"

namespace RavenEngine {

CollisionManager& CollisionManager::GetInstance() {
    static CollisionManager instance;
    return instance;
}

void CollisionManager::AddShape(Shape2D* shape) {
    shapes.push_back(shape);
    std::cout << "COLLISIONMANAGER::ADDSHAPE Added shape with ID: " << shape->GetID() << std::endl;
}

void CollisionManager::RemoveShape(Shape2D* shape) {
    shapes.erase(std::remove(shapes.begin(), shapes.end(), shape), shapes.end());
}

bool CollisionManager::CheckCollisionForShape(Shape2D* shape) {
    if (!shape->IsCollisionEnabled()) {
        return false; // Skip collision check if collision is disabled for this shape
    }

    for (auto& otherShape : shapes) {
        if (shape != otherShape && otherShape->IsCollisionEnabled() && CheckCollision(shape, otherShape)) {
            return true;
        }
    }

    return false;
}

void CollisionManager::CheckCollisions() {
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::cout << "COLLISIONMANAGER::CHECKCOLLISIONS Checking collisions for shape with ID: " << shapes[i]->GetID() << std::endl;
        for (size_t j = i + 1; j < shapes.size(); ++j) {
            if (CheckCollision(shapes[i], shapes[j])) {
                // Log the collision event to the console
                // std::cout << "Collision detected between " 
                //           << Shape2D::GetTypeName(shapes[i]->GetSpecificType()) << " ID: " << shapes[i]->GetID()
                //           << " and " 
                //           << Shape2D::GetTypeName(shapes[j]->GetSpecificType()) << " ID: " << shapes[j]->GetID()
                //           << std::endl;

                // Handle collision event here
            }
        }
    }
}

std::vector<glm::vec2> CollisionManager::GetAxes(Shape2D* a, Shape2D* b) {
    std::vector<glm::vec2> axes;
    auto normalsA = a->GetNormals();
    auto normalsB = b->GetNormals();

    // std::cout << "Shape A normals: ";
    // for (const auto& normal : normalsA) {
    //     std::cout << "(" << normal.x << ", " << normal.y << ") ";
    // }
    // std::cout << std::endl;

    // std::cout << "Shape B normals: ";
    // for (const auto& normal : normalsB) {
    //     std::cout << "(" << normal.x << ", " << normal.y << ") ";
    // }
    // std::cout << std::endl;

    axes.insert(axes.end(), normalsA.begin(), normalsA.end());
    axes.insert(axes.end(), normalsB.begin(), normalsB.end());

    // std::cout << "Combined axes: ";
    // for (const auto& axis : axes) {
    //     std::cout << "(" << axis.x << ", " << axis.y << ") ";
    // }
    // std::cout << std::endl;

    return axes;
}

bool CollisionManager::CheckCollision(Shape2D* a, Shape2D* b) {
    bool isColliding = CheckSATCollision(a, b);
    //std::cout << "Collision check between shapes: " << (isColliding ? "Colliding" : "Not colliding") << std::endl;
    return isColliding;
}

bool CollisionManager::Overlap(const Shape2D::Projection& projA, const Shape2D::Projection& projB) {
    bool isOverlapping = !(projA.max < projB.min || projB.max < projA.min);
    //std::cout << "Overlap check: " << (isOverlapping ? "Overlapping" : "Not overlapping") << std::endl;
    return isOverlapping;
}

bool CollisionManager::CheckSATCollision(Shape2D* a, Shape2D* b) {
    std::vector<glm::vec2> axes = GetAxes(a, b);

    for (const auto& axis : axes) {
        Shape2D::Projection projA = a->ProjectOntoAxis(axis);
        Shape2D::Projection projB = b->ProjectOntoAxis(axis);

        if (!Overlap(projA, projB)) {
            //std::cout << "Found an axis with no overlap. Shapes are not colliding." << std::endl;
            return false; // No collision if there's an axis with no overlap
        }
    }

    //std::cout << "All axes have overlap. Shapes are colliding." << std::endl;
    return true; // Collision if all axes have overlap
}


} // namespace RavenEngine