// triangle.cpp

// #include section
// #####################
// Standard library includes
#include <iostream> // Include the iostream library to use std::cout

// Third party includes
#include <glm/gtx/string_cast.hpp> // Include the glm/gtx/string_cast.hpp library to use glm::to_string

// Local project includes
#include "Triangle.h"

namespace RavenEngine {

Triangle::Triangle() { // Default constructor
    type = Type::Triangle; // Set the type member to Shape2D::Type::Triangle
    vertices[0] = glm::vec3(0.0f, 0.0f, 0.0f); // Set the first vertex to zero
    vertices[1] = glm::vec3(0.0f, 0.0f, 0.0f); // Set the second vertex to zero
    vertices[2] = glm::vec3(0.0f, 0.0f, 0.0f); // Set the third vertex to zero
}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) { // Constructor
    type = Type::Triangle; // Set the type member to Shape2D::Type::Triangle
    vertices[0] = v1; // Set the first vertex
    vertices[1] = v2; // Set the second vertex
    vertices[2] = v3; // Set the third vertex
}

Triangle::~Triangle() {                                                    // Destructor
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Triangle::Create() {                                                  // Create method
    GLfloat vertices[] = {
        // Adjusted Y-coordinates
        0.0f, -0.5f, 0.0f, // Top (Inverted Y)
        -0.5f, 0.5f, 0.0f, // Bottom Left
        0.5f, 0.5f, 0.0f  // Bottom Right
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
    std::cout << "Triangle VAO: " << VAO << std::endl;
    std::cout << "Triangle VBO: " << VBO << std::endl;
}

// Render method
void Triangle::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    // Render the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

} // namespace RavenEngine