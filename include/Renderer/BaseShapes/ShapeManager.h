#pragma once

#include <vector>
#include <memory>
#include "Shape.h" // Include the Shape base class
#include "SettingsManager.h" // Include the SettingsManager class

namespace RavenEngine {

class ShapeManager {
public:
    ShapeManager(const std::string& settingsFilePath);
    ~ShapeManager();

    void AddShape(std::shared_ptr<Shape> shape);
    void RenderShapes(ShaderManager& shaderManager, const std::string& shaderName, const glm::mat4& projectionMatrix);
    void SetAspectRatio(float newAspectRatio);

private:
    std::vector<std::shared_ptr<Shape>> shapes; // Store shapes
    float aspectRatio;
    SettingsManager settingsManager; // Add a SettingsManager instance
};

} // namespace RavenEngine