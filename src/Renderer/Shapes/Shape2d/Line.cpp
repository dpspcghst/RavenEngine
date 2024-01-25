// Line.cpp

// #include section
// #####################
// Standard library includes

// Third party includes
#include <glm/glm.hpp>

// Local project includes
#include "Line.h"

namespace RavenEngine {

Line::Line(const glm::vec2& startPoint, const glm::vec2& endPoint) 
    : Shape2D(glm::vec3((startPoint + endPoint) / 2.0f, 0.0f), Shape2D::Type::Line), start(startPoint), end(endPoint) {
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

    // Define the vertices of the line
    glm::vec2 vertices[] = {start, end};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Line::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

} // namespace RavenEngine