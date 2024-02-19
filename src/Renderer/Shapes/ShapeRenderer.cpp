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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    if (textureId != -1 && TextureManager::GetInstance().HasTexture(textureId)) {
        // Activate the texture unit before binding
        glActiveTexture(GL_TEXTURE0);

        // Bind the texture
        TextureManager::GetInstance().BindTexture(textureId);

        auto shaderProgram = shape->GetShaderProgram();
        GLint textureUniformLoc = glGetUniformLocation(shaderProgram, "u_Texture");
        GLint hasTextureUniformLoc = glGetUniformLocation(shaderProgram, "u_HasTexture");

        // Bind the texture to the active texture unit
        glUniform1i(textureUniformLoc, 0); // Texture unit 0
        glUniform1i(hasTextureUniformLoc, 1); // Indicates a texture is bound

        // Set texture transformation uniforms
        auto& textureManager = TextureManager::GetInstance();
        auto textureInfo = textureManager.GetTexture(textureId);

        glUniform2f(glGetUniformLocation(shaderProgram, "textureScale"), textureInfo.scaleX, textureInfo.scaleY);
        glUniform2f(glGetUniformLocation(shaderProgram, "textureTranslation"), textureInfo.position.x, textureInfo.position.y);
        glUniform1f(glGetUniformLocation(shaderProgram, "textureRotation"), textureInfo.rotation);

        std::cout << "ShapeRenderer::BindTextureIfAvailable - Bound texture with ID: " << textureId << std::endl;
    } else {
        auto shaderProgram = shape->GetShaderProgram();
        GLint hasTextureUniformLoc = glGetUniformLocation(shaderProgram, "u_HasTexture");
        glUniform1i(hasTextureUniformLoc, 0); // Indicates no texture is bound
    }
}

}
