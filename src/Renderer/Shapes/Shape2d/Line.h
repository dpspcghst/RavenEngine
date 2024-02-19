// line.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

// Third-party includes
#include <glad/glad.h>
#include <glm/glm.hpp>
// Raven includes
#include "Shape2D.h"

namespace RavenEngine {
class Line : public Shape2D {
public:
        Line(); // Default constructor
        Line(const glm::vec3& startPoint, const glm::vec3& endPoint);
        virtual ~Line();

        void Create() override;
        void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;

        int GetVertexCount() const override;

        // Add a method to set the texture ID
        void SetTextureId(int id) { textureId = id; }
        // Add a method to get the texture ID
        int GetTextureId() const { return textureId; }

        std::vector<glm::vec3> GetVertices() const override {
        // For a line, the vertices are the start and end points.
        return {start, end};
    }

    std::vector<glm::vec2> GetNormals() const override {
        glm::vec2 direction = glm::normalize(glm::vec2(end - start));
        return {glm::vec2(-direction.y, direction.x), glm::vec2(direction.y, -direction.x)};
    }

    Projection ProjectOntoAxis(const glm::vec2 &axis) const override {
        float startProjection = glm::dot(glm::vec2(start), axis);
        float endProjection = glm::dot(glm::vec2(end), axis);
        return {std::min(startProjection, endProjection), std::max(startProjection, endProjection)};
    }

private:
        glm::vec3 start{0.0f, 0.0f, 0.0f}, end{0.0f, 0.0f, 0.0f}; // Initialize to default values
        GLuint VAO = 0, VBO = 0;

        // Add a member variable to store the texture ID
        int textureId;
    };
} // namespace RavenEngine