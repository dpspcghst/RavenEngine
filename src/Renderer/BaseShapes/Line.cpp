// Line.cpp
#include <glm/glm.hpp> // Include the glm header
#include "../../include/Renderer/BaseShapes/Line.h"

namespace RavenEngine {

Line::Line(const glm::vec3& startPoint, const glm::vec3& endPoint)
    : Shape(), start(startPoint), end(endPoint) {} // Call the Shape constructor

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
    glm::vec3 vertices[] = {start, end};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Line::Render(ShaderManager& shaderManager, const std::string& shaderName) {
    shaderManager.UseShader(shaderName);
    shaderManager.SetUniform(shaderName, transformMatrix);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

} // namespace RavenEngine