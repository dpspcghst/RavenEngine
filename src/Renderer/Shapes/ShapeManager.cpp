// shapemanager.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third party includes
#include <glm/gtx/string_cast.hpp>

// Local project includes
#include "ShapeManager.h"
#include "SettingsManager.h"
#include "Shape2D/Shape2D.h"

namespace RavenEngine {

ShapeManager::ShapeManager() { // Constructor
    // Get the singleton instance of SettingsManager
    SettingsManager& settingsManager = SettingsManager::GetInstance();

    // Use settingsManager to get the resolution width and height
    int screenWidth = settingsManager.GetResolutionWidth();
    int screenHeight = settingsManager.GetResolutionHeight();

    aspectRatio = static_cast<float>(screenWidth) / screenHeight; // Calculate aspect ratio
}

ShapeManager::~ShapeManager() {} // Destructor

void ShapeManager::AddShape(std::shared_ptr<Shape2D> shape2D) {
    ValidateShape(shape2D);
    shapes2D.push_back(shape2D); // Add the shape to the vector of shapes
}

void ShapeManager::ValidateShape(std::shared_ptr<Shape2D> shape2D) {
    if (!shape2D) {
        std::cout << "Cannot add null shape" << std::endl;
        throw std::runtime_error("Cannot add null shape");
    }

    glm::vec3 newSize = shape2D->GetSize(); // Get the size of the shape

    if (newSize.x < 0 || newSize.y < 0 || newSize.z < 0) {
        std::cout << "Invalid shape size: " << glm::to_string(newSize) << std::endl;
        throw std::runtime_error("Invalid shape size");
    }
}

void ShapeManager::RenderShapes() {
    if (!camera) {
        throw std::runtime_error("Camera not set in ShapeManager");
    }

    std::cout << "Rendering shapes" << std::endl;

    for (auto& shape : shapes2D) {
        // Render the shape with the camera's view and projection matrices
        shape->Render(camera->GetViewMatrix(), camera->GetProjectionMatrix());
    }
}

} // namespace RavenEngine