// shapemanager.h
#pragma once

// #include section
// #####################
// Standard library includes
#include <vector>
#include <memory>

// Third party includes

// Raven includes
#include "Shape2D/Shape2D.h"
#include "SettingsManager.h"
#include "../../../Assets/Shaders/ShaderManager.h"
#include "../Camera.h"

namespace RavenEngine {

class ShapeManager {
public:
    ShapeManager(); // Constructor without parameters
    ~ShapeManager();

    void AddShape(std::shared_ptr<Shape2D> shape);

    void ValidateShape(std::shared_ptr<Shape2D> shape);
    void RenderShapes();
    void RemoveShape(std::shared_ptr<Shape2D> shape);
    void SetCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }

    Shape2D* GetShape(Shape2D::Type shapeType) const {
        for (const auto& shape2D : shapes2D) {
            if (shape2D->GetType() == shapeType) {
                return shape2D.get();
            }
        }
        throw std::runtime_error("No shape of this type in the manager");
    }

private:
    std::vector<std::shared_ptr<Shape2D>> shapes2D; // Store shapes in a vector
    float aspectRatio;
    std::shared_ptr<Camera> camera; // Camera
};

} // namespace RavenEngine