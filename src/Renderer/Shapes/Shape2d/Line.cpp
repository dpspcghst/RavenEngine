// Line.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third-party includes
#include <glm/gtc/type_ptr.hpp>

// Raven includes
#include "Line.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Texture/TextureManager.h"

namespace RavenEngine {

Line::Line() : start(glm::vec3(0.0f)), end(glm::vec3(1.0f, 0.0f, 0.0f)) { // Default to a horizontal line of unit length
}

Line::Line(const glm::vec3& startPoint, const glm::vec3& endPoint)  
    : Shape2D(), start(startPoint), end(endPoint), textureId(0) {
    color = glm::vec4(1.0f); // Default color is white
    type = Shape2D::Type::Line; // Set shape type
}

Line::~Line() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Line::Create() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glm::vec3 vertices[] = {start, end};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Line::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());

    if (shaderProgramPtr) {
        shaderProgramPtr->Use();

        glUniformMatrix4fv(shaderProgramPtr->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(GetTransformMatrix()));
        glUniformMatrix4fv(shaderProgramPtr->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(shaderProgramPtr->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        TextureInfo textureInfo = TextureManager::GetInstance().GetTexture(GetTextureId());
        if (textureInfo.id != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureInfo.id);
            shaderProgramPtr->SetUniform("u_Texture", 0);
        } else {
            shaderProgramPtr->SetUniform("u_Texture", 0);
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
        glBindVertexArray(0);
    } else {
        std::cerr << "Line::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}

int Line::GetVertexCount() const {
    return 2; // Assuming a line is defined by 2 vertices
}

} // namespace RavenEngine
