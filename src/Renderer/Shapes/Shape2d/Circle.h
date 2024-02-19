// Circle.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <vector>
// Third-party includes
#include <glad/glad.h>
#include <glm/glm.hpp>
// Raven includes
#include "Shape2D.h"

namespace RavenEngine {

class Circle : public Shape2D {
public:
    // Adjusted constructor to accept xRadius and yRadius
    Circle();
    Circle(float xRadius, float yRadius, int segments);
    virtual ~Circle();

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;
    int GetVertexCount() const override;

    // Methods to set and get radii
    void SetRadii(float xRadius, float yRadius);
    std::pair<float, float> GetRadii() const;

    // Adjusted to manage a texture ID
    void SetTextureId(GLuint id);
    GLuint GetTextureId() const;

    const float PI = 3.14159265358979323846f;

    std::vector<glm::vec3> GetVertices() const override {
        return {glm::vec3(xRadius, yRadius, 0.0f)};
    }

    std::vector<glm::vec2> GetNormals() const override {
        return {};
    }

    Projection ProjectOntoAxis(const glm::vec2 &axis) const override {
        float centerProjection = glm::dot(glm::vec2(xRadius, yRadius), axis);
        float radius = glm::length(glm::vec2(xRadius, yRadius));
        return {centerProjection - radius, centerProjection + radius};
    }

private:
    float xRadius, yRadius; // Two radii for the ellipse
    int segments;
    GLuint textureId; // OpenGL texture ID

    void CalculateVertices();
};

} // namespace RavenEngine