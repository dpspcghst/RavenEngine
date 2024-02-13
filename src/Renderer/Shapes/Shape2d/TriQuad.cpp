// triquad.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes
#include <glm/gtc/type_ptr.hpp>
// Raven includes
#include "TriQuad.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Texture/TextureManager.h"

namespace RavenEngine {

TriQuad::TriQuad() : Shape2D(), textureId(0) {
    type = Type::TriQuad;
}

TriQuad::~TriQuad() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TriQuad::Create() {
    GLfloat vertices[] = {
        // First triangle
        -0.5f,  0.5f, 0.0f,  // Top Left
        -0.5f, -0.5f, 0.0f,  // Bottom Left
         0.5f, -0.5f, 0.0f,   // Bottom Right
        // Second triangle
         0.5f, -0.5f, 0.0f,   // Bottom Right again
         0.5f,  0.5f, 0.0f,   // Top Right
        -0.5f,  0.5f, 0.0f    // Top Left again
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void TriQuad::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());

    if (shaderProgramPtr) {
        GLuint shaderProgramID = shaderProgramPtr->GetID();
        glUseProgram(shaderProgramID);

        // Set the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        TextureInfo textureInfo = TextureManager::GetInstance().GetTexture(GetTextureId());
        if (textureInfo.id != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureInfo.id);
            shaderProgramPtr->SetUniform("u_Texture", 0);
        } else {
            shaderProgramPtr->SetUniform("u_Texture", 0);
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, GetVertexCount());
        glBindVertexArray(0);
    } else {
        std::cerr << "TriQuad::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}

int TriQuad::GetVertexCount() const {
    return 6;
}

} // namespace RavenEngine