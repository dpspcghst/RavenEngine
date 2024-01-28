// Circle.cpp

// #include section
// #####################
// Standard library includes
#include <vector>
// Third party includes
#include <glm/gtc/type_ptr.hpp>
// Raven includes
#include "Circle.h"

namespace RavenEngine {
    Circle::Circle() : radius(0.5f), segments(36) {
        type = Type::Circle;
    }

    Circle::Circle(float radius, int segments) : radius(radius), segments(segments) {
        type = Type::Circle;
    }

    Circle::~Circle() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void Circle::Create() {
        std::vector<GLfloat> vertices;
        for (int i = 0; i <= segments; ++i) {
            float theta = 2.0f * 3.1415926f * float(i) / float(segments);
            float dx = radius * cosf(theta);
            float dy = radius * sinf(theta);
            vertices.push_back(dx);
            vertices.push_back(dy);
            vertices.push_back(0.0f);
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);
    }

    void Circle::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
        glUseProgram(shaderProgram);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 transformMatrix = projectionMatrix * viewMatrix * modelMatrix;

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transformMatrix"), 1, GL_FALSE, glm::value_ptr(transformMatrix));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 1);
        glBindVertexArray(0);
    }

    int Circle::GetVertexCount() const {
        // Implement this function to return the number of vertices in the circle.
        // For example, if each segment corresponds to one vertex, you might return:
        return segments + 1;
    }
}