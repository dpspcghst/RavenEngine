// Circle.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third-party includes
#include <glm/gtc/type_ptr.hpp>

// Raven includes
#include "Circle.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Texture/TextureManager.h"

namespace RavenEngine {
Circle::Circle() : Shape2D(), xRadius(1.0f), yRadius(1.0f), segments(32), textureId(0) {
    type = Type::Circle;
    Create();
}
Circle::Circle(float xRadius, float yRadius, int segments)
    : Shape2D(), xRadius(xRadius), yRadius(yRadius), segments(segments > 0 ? segments : 32) {
    type = Type::Circle;
}

Circle::~Circle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Circle::Create() {
    std::vector<GLfloat> vertices;
    // Center vertex for TRIANGLE_FAN, with center texture coordinate
    vertices.insert(vertices.end(), {0.0f, 0.0f, 0.0f, 0.5f, 0.5f});

    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * PI * float(i) / float(segments);
        float dx = xRadius * cosf(theta);
        float dy = yRadius * sinf(theta);

        // Position
        vertices.insert(vertices.end(), {dx, dy, 0.0f});

        // Texture coordinates, mapping the ellipse onto a unit square texture
        vertices.insert(vertices.end(), {(cosf(theta) + 1.0f) * 0.5f, (sinf(theta) + 1.0f) * 0.5f});
    }

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Texture Coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Circle::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());

    if (shaderProgramPtr) {
        GLuint shaderProgramID = shaderProgramPtr->GetID();
        glUseProgram(shaderProgramID);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);

        glBindVertexArray(0);
    } else {
        std::cerr << "Circle::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}

int Circle::GetVertexCount() const {
    return segments + 2;
}

} // namespace RavenEngine