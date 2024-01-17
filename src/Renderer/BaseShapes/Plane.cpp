// Plane.cpp
#include <glm/glm.hpp>
#include "../../include/Renderer/BaseShapes/Plane.h"

namespace RavenEngine {

Plane::Plane() : Shape() {}

Plane::~Plane() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Plane::Create() {
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

} // namespace RavenEngine