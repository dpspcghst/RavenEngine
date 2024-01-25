// triquad.cpp

// #include section
// #####################

// Local Project Includes
#include "TriQuad.h"

namespace RavenEngine {

TriQuad::TriQuad() {
    type = Type::TriQuad; // Set the type member to Type::TriQuad
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
        0.5f, -0.5f, 0.0f,   // Bottom Right
        0.5f,  0.5f, 0.0f,   // Top Right
        -0.5f,  0.5f, 0.0f   // Top Left
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TriQuad::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    // Bind VAO and draw triangles
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind
    glBindVertexArray(0);
}

} // namespace RavenEngine