// triangle.cpp

// #include section
// #####################
// Standard library includes
#include <iostream> // Include the iostream library to use std::cout

// Third party includes
#include <glm/gtx/string_cast.hpp> // Include the glm/gtx/string_cast.hpp library to use glm::to_string
#include <glm/gtc/type_ptr.hpp> // Include the glm/gtc/type_ptr.hpp library to use glm::value_ptr

// Local project includes
#include "Triangle.h"

namespace RavenEngine {

Triangle::Triangle() { // Default Triangle Constructor
    type = Type::Triangle; // Adding Triang to Shape2D shape Type Shape2D::Type::Triangle
    vertices[0] = glm::vec3(0.0f, -0.5f, 0.0f); // Set the first vertex to the top of the triangle
    vertices[1] = glm::vec3(-0.5f, 0.5f, 0.0f); // Set the second vertex to the bottom left of the triangle
    vertices[2] = glm::vec3(0.5f, 0.5f, 0.0f); // Set the third vertex to the bottom right of the triangle
    //std::cout << "Default Triangle created with vertices: " << glm::to_string(vertices[0]) << ", " << glm::to_string(vertices[1]) << ", " << glm::to_string(vertices[2]) << std::endl;
}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) { // Constructor
    type = Type::Triangle; // Set the type member to Shape2D::Type::Triangle
    vertices[0] = v1; // Set the first vertex
    vertices[1] = v2; // Set the second vertex
    vertices[2] = v3; // Set the third vertex
    //std::cout << "Triangle created with vertices: " << glm::to_string(vertices[0]) << ", " << glm::to_string(vertices[1]) << ", " << glm::to_string(vertices[2]) << std::endl;
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
    
    //std::cout << "Creating Triangle with vertices: " << vertices[0] << ", " << vertices[1] << ", " << vertices[2] << std::endl;
    
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
    //std::cout << "Triangle VAO: " << VAO << std::endl;
    //std::cout << "Triangle VBO: " << VBO << std::endl;
}

void Triangle::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    // Bind the shader program
    glUseProgram(shaderProgram);

    // Calculate the transform matrix
    glm::mat4 modelMatrix = glm::mat4(1.0f); // Identity matrix for the model matrix
    glm::mat4 transformMatrix = projectionMatrix * viewMatrix * modelMatrix;

    // Pass the transform matrix to the shader
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transformMatrix"), 1, GL_FALSE, glm::value_ptr(transformMatrix));

    // Render the triangle
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

} // namespace RavenEngine