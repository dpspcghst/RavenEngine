// scenegraphrenderer.cpp
// #####################
// #include section
// Standard library includes
#include <iostream>
// Third-party includes
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
// Raven includes
#include "SceneGraphRenderer.h"
#include "../Renderer/Shapes/ShapeRenderer.h"
#include "../Renderer/Shaders/ShaderManager.h"
#include "../Renderer/Texture/TextureManager.h"

namespace RavenEngine {

SceneGraphRenderer::SceneGraphRenderer(std::shared_ptr<Camera> camera)
    : camera(std::move(camera)), shapeRenderer(std::make_unique<ShapeRenderer>()) {
    if (!this->camera) {
        std::cerr << "Error: Camera is null.\n";
        return;
    }

    // Optional: Debug output
    std::cout << "Camera initialized with view and projection matrices.\n";
}

void SceneGraphRenderer::RenderScene(const SceneNode& rootNode) {
    RenderNode(rootNode, glm::mat4(1.0f)); // Start with an identity matrix for the root
}

void SceneGraphRenderer::RenderNode(const SceneNode& node, const glm::mat4& parentTransform) {
    glm::mat4 modelMatrix = parentTransform * node.GetTransformMatrix();

    auto shape = node.GetShape();
    if (shape) {
        // Use ShapeRenderer to render the shape
        shapeRenderer->RenderShape(shape, modelMatrix, camera->GetViewMatrix(), camera->GetProjectionMatrix());
    }

    for (const auto& child : node.GetChildren()) {
        RenderNode(*child, modelMatrix); // Recursively render children
    }
}

} // namespace RavenEngine