// Plane.cpp
#include "../../include/Renderer/Primitives/Plane.h"

namespace RavenEngine {

Plane::Plane() : VAO(0), VBO(0) {
    // Initialize the VAO and VBO here
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
}

Plane::~Plane() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Plane::Create() {
    // This method is empty as we initialize the VAO and VBO in the constructor
}

void Plane::Render() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void Plane::SetSize(float width, float height) {
    size = glm::vec2(width, height);

    GLfloat halfWidth = size.x / 2.0f;
    GLfloat halfHeight = size.y / 2.0f;

    GLfloat vertices[] = {
        // Positions
        position.x - halfWidth,  position.y + halfHeight, 0.0f,  // Top Left
        position.x + halfWidth,  position.y + halfHeight, 0.0f,  // Top Right
        position.x - halfWidth,  position.y - halfHeight, 0.0f,  // Bottom Left
        position.x + halfWidth,  position.y - halfHeight, 0.0f   // Bottom Right
    };

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::SetPosition(float x, float y) {
    position = glm::vec2(x, y);
    SetSize(size.x, size.y); // Update the plane's position
}

} // namespace RavenEngine