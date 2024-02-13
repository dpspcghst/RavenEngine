// point.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes
#include <glm/gtc/type_ptr.hpp>
// Raven Includes
#include "Point.h"
#include "Shape2D.h" // Include Shape2D instead of Shape

namespace RavenEngine {

Point::Point(const glm::vec3& position) : Shape2D() {
    // Set the type member to Type::Point and initialize the vertex with default texture coordinates
    type = Type::Point;
    vertex = {position, glm::vec2(0.0f, 0.0f)}; // Default texture coordinates (unused)
}

Point::~Point() {
    // Cleanup handled by Shape2D destructor
}

void Point::Create() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &vertex, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Texture coordinate attribute (unused but set up for consistency)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Point::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());

    if (shaderProgramPtr) {
        GLuint shaderProgramID = shaderProgramPtr->GetID();
        glUseProgram(shaderProgramID);

        // Set the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // Texture setup could be omitted for Point, as it doesn't use textures
        // Binding and rendering the point
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 1);
        glBindVertexArray(0);
    } else {
        std::cerr << "Point::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}

int Point::GetVertexCount() const {
    return 1; // Only one vertex for a point
}

} // namespace RavenEngine