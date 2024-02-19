// point.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

// Third-party includes
#include <glm/glm.hpp>
// Raven includes
#include "Shape2D.h"

namespace RavenEngine {

class Point : public Shape2D {
public:
    Point() = default;
    Point(const glm::vec3& position);
    ~Point() override;

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;
    int GetVertexCount() const override;

    std::vector<glm::vec3> GetVertices() const override {
        // For a point, the only vertex is the point itself.
        return {vertex.position};
    }

    std::vector<glm::vec2> GetNormals() const override {
        // A point doesn't have any normals, because it doesn't have any area.
        return {};
    }

    Projection ProjectOntoAxis(const glm::vec2 &axis) const override {
        // For a point, the projection onto any axis is just the point itself.
        float projection = glm::dot(glm::vec2(vertex.position), axis);
        return {projection, projection};
    }

private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords; // Default texture coordinates, unused for Point
    };

    Vertex vertex;
};

} // namespace RavenEngine