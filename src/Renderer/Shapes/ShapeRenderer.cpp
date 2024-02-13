// shaperenderer.cpp
// ################
// #include section
// ################
// Standard library includes
#include <iostream>

// Third-party includes

// Raven includes
#include "ShapeRenderer.h"

namespace RavenEngine {
ShapeRenderer::ShapeRenderer() {}
ShapeRenderer::~ShapeRenderer() {}

void ShapeRenderer::RenderShape(const std::shared_ptr<Shape>& shape, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    if (!shape) { // If the shape is null
        std::cerr << "ShapeRenderer::RenderShape - Attempted to render a null shape." << std::endl;
        return;
    }

    auto shaderProgramPtr = ShaderManager::GetInstance().GetShader(shape->GetShaderName());
    if (!shaderProgramPtr) { // If the shader program is not available
        std::cerr << "ShapeRenderer::RenderShape - Failed to retrieve shader program for '" << shape->GetShaderName() << "'." << std::endl;
        // Set a default color using the shader
        shaderProgramPtr = ShaderManager::GetInstance().GetShader("defaultColorShader");
        if (!shaderProgramPtr) { // If the default color shader is not available
            std::cerr << "ShapeRenderer::RenderShape - Failed to retrieve default color shader." << std::endl;
            return;
        }
    }

    shaderProgramPtr->Use();
    SetShaderUniforms(shaderProgramPtr, modelMatrix, viewMatrix, projectionMatrix, shape);
    BindTextureIfAvailable(shape);

    shape->Render(viewMatrix, projectionMatrix);
}

void ShapeRenderer::SetShaderUniforms(std::shared_ptr<ShaderProgram> shaderProgram, const glm::mat4& modelMatrix, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, const std::shared_ptr<Shape>& shape) {
    shaderProgram->SetUniform("model", modelMatrix);
    shaderProgram->SetUniform("view", viewMatrix);
    shaderProgram->SetUniform("projection", projectionMatrix);

    auto uboName = shape->GetMaterialUBOName();
    auto uboProps = UniformBufferManager::GetInstance().GetUBOProperties(uboName);
    if (uboProps.bufferID != 0) {
        glUniformBlockBinding(shaderProgram->GetID(), shaderProgram->GetUniformBlockIndex("MaterialProperties"), 0);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboProps.bufferID);
    }
}

void ShapeRenderer::BindTextureIfAvailable(const std::shared_ptr<RavenEngine::Shape>& shape) {
    int textureId = shape->GetTextureId();
    if (textureId != -1 && TextureManager::GetInstance().HasTexture(textureId)) { // If the shape texture is == -1, it means no texture is set
        auto textureInfo = TextureManager::GetInstance().GetTexture(textureId);
        if (textureInfo.id != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureInfo.id);
            // Assuming shader uses "u_Texture" as the sampler2D uniform name
            glUniform1i(glGetUniformLocation(shape->GetShaderProgram(), "u_Texture"), 0);
            // Set the u_HasTexture uniform to 1
            glUniform1i(glGetUniformLocation(shape->GetShaderProgram(), "u_HasTexture"), 1);

            std::cout << "SHAPERENDERER::BINDTEXTUREIFAVAILABLE Bound texture with ID: " << textureInfo.id << std::endl;
        } else {
            std::cerr << "SHAPERENDERER::BINDTEXTUREIFAVAILABLE Texture with id " << textureId << " not found." << std::endl;
        }
    } else {
        // Set the u_HasTexture uniform to 0
        glUniform1i(glGetUniformLocation(shape->GetShaderProgram(), "u_HasTexture"), 0);
    }
}
}
