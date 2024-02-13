// Rect.cpp

// #include section
// #####################
// standard library includes
#include <iostream>

// third party includes
#include <glm/gtc/type_ptr.hpp>

// Raven includes
#include "Rect.h"
#include "../../Shaders/ShaderManager.h"

namespace RavenEngine {

Rect::Rect() : Shape2D() {
    type = Type::Rect;
}

Rect::~Rect() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Rect::Create() {
    GLfloat vertices[] = {
        // Positions
        -0.5f,  0.5f, 0.0f,  // Top Left
         0.5f,  0.5f, 0.0f,  // Top Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
         0.5f, -0.5f, 0.0f   // Bottom Right
    };

    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO
    glBindVertexArray(0);
}

void Rect::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<RavenEngine::ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());

    if (shaderProgramPtr) {
        GLuint shaderProgramID = shaderProgramPtr->GetID();
        glUseProgram(shaderProgramID);

        // Set the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // Bind VAO and draw Rect
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Unbind
        glBindVertexArray(0);
    } else {
        std::cerr << "Rect::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}

int Rect::GetVertexCount() const {
    return 4;
}

} // namespace RavenEngine