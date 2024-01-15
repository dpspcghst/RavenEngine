// Plane.cpp
#include "../../include/Renderer/Primitives/Plane.h"

namespace RavenEngine {

Plane::Plane() : VAO(0), VBO(0) {}

Plane::~Plane() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Plane::Create() {
    GLfloat vertices[] = {
        // Positions
        -0.5f,  0.5f, 0.0f,  // Top Left
        0.5f,  0.5f, 0.0f,   // Top Right
        -0.5f, -0.5f, 0.0f,  // Bottom Left
        0.5f, -0.5f, 0.0f    // Bottom Right
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

void Plane::Render() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

} // namespace RavenEngine