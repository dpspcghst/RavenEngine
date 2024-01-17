#include "../../../include/Renderer/BaseShapes/ShapeManager.h"

namespace RavenEngine {

ShapeManager::ShapeManager(const std::string& settingsFilePath) 
    : settingsManager(settingsFilePath) {
    // Retrieve the screen width and height from the settings
    int screenWidth = settingsManager.GetResolutionWidth();
    int screenHeight = settingsManager.GetResolutionHeight();

    // Calculate the aspect ratio
    aspectRatio = static_cast<float>(screenWidth) / screenHeight;
}

ShapeManager::~ShapeManager() {}

void ShapeManager::AddShape(std::shared_ptr<Shape> shape) {
    glm::vec3 newSize = shape->GetSize();
    newSize.x *= aspectRatio;
    shape->SetSize(newSize);
    shapes.push_back(shape);
}

void ShapeManager::RenderShapes(ShaderManager& shaderManager, const std::string& shaderName, const glm::mat4& projectionMatrix) {
    for (auto& shape : shapes) {
        shape->Render(shaderManager, shaderName, projectionMatrix);
    }
}

void ShapeManager::SetAspectRatio(float newAspectRatio) {
    aspectRatio = newAspectRatio;
    for (auto& shape : shapes) {
        glm::vec3 newSize = shape->GetSize();
        newSize.x *= aspectRatio;
        shape->SetSize(newSize);
    }
}

} // namespace RavenEngine