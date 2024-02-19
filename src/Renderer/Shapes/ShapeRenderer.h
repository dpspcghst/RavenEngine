// shaperenderer.h
// ################
#pragma once
// ################
// #include section
// Standard library includes
#include <memory>

// Third-party includes
#include <glm/glm.hpp>

// Raven includes
#include "Shape.h"
#include "../Shaders/ShaderManager.h"
#include "../Texture/TextureManager.h"
#include "../UBO/UniformBufferManager.h"

namespace RavenEngine {

class ShapeRenderer {
public:
    ShapeRenderer();
    ~ShapeRenderer();

    void RenderShape(const std::shared_ptr<Shape>& shape, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

private:
    
    void SetShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::shared_ptr<Shape>& shape);
    void BindTextureIfAvailable(const std::shared_ptr<Shape>& shape);

};

} // namespace RavenEngine