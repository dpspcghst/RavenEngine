// Cube.cpp

// #include section
// #####################
// Standard library includes
#include <array> 
// Third party includes
#include <glm/gtc/type_ptr.hpp>
// Raven includes
#include "Cube.h"

namespace RavenEngine {

Cube::Cube() {

}

Cube::Cube(GLuint shaderProgram) : shaderProgram(shaderProgram) {
    type = Type::Cube;
    ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    specular = glm::vec3(0.5f, 0.5f, 0.5f);
    shininess = 32.0f;
}

Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Cube::Create() {
    // Define the vertices for a cube
    std::array<float, 216> vertices = {
        // positions            // normals
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,     -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,     -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,      1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,      1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,      1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,      1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f
    };

    // Generate and bind a Vertex Array Object
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind a Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO (safe practice)
    glBindVertexArray(0);
}

void Cube::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    glUseProgram(shaderProgram);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 transformMatrix = projectionMatrix * viewMatrix * modelMatrix;

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transformMatrix"), 1, GL_FALSE, glm::value_ptr(transformMatrix));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, GetVertexCount());
    glBindVertexArray(0);
}

int Cube::GetVertexCount() const {
    // A cube has 6 faces, each face is made up of 2 triangles, and each triangle has 3 vertices
    return 6 * 2 * 3;
}
    
    } // namespace RavenEngine