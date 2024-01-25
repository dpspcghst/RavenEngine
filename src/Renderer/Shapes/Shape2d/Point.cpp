// point.cpp

// #include section
// #####################
// Raven Includes
#include "Point.h"
#include "Shape2D.h" // Include Shape2D instead of Shape

namespace RavenEngine {

Point::Point(const glm::vec3& position){
    type = Type::Point; // Set the type member to Type::Point
    SetPosition(position); // Set the position member
}

Point::~Point() {
    // No need to delete VAO and VBO here, it's done in the Shape2D destructor
}

void Point::Create() {
    // Generate and bind VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &position, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Point::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    // Bind VAO and draw point
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 1);
    // Unbind
    glBindVertexArray(0);
}

} // namespace RavenEngine