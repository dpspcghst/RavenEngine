// TriQuad.h
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
#include "Shape2d.h" 

namespace RavenEngine {

class TriQuad : public Shape2D {
public:
    TriQuad();
    virtual ~TriQuad();

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;

    int GetVertexCount() const override;

    int GetTextureId() const { return textureId; }
    void SetTextureId(int id) { textureId = id; }

    std::vector<glm::vec3> GetVertices() const override {
        // For a quadrilateral, the vertices are the four corners.
        // Assuming the vertices are ordered in a counterclockwise manner.
        return {vertices[0].position, vertices[1].position, vertices[2].position, vertices[3].position};
    }

    std::vector<glm::vec2> GetNormals() const override {
        // For a quadrilateral, the normals are perpendicular to the edges.
        // We can calculate them by taking the cross product of the edge vectors.
        glm::vec2 edge1 = glm::normalize(glm::vec2(vertices[1].position - vertices[0].position));
        glm::vec2 edge2 = glm::normalize(glm::vec2(vertices[2].position - vertices[1].position));
        glm::vec2 edge3 = glm::normalize(glm::vec2(vertices[3].position - vertices[2].position));
        glm::vec2 edge4 = glm::normalize(glm::vec2(vertices[0].position - vertices[3].position));
        return {glm::vec2(-edge1.y, edge1.x), glm::vec2(-edge2.y, edge2.x), glm::vec2(-edge3.y, edge3.x), glm::vec2(-edge4.y, edge4.x)};
    }

    Projection ProjectOntoAxis(const glm::vec2 &axis) const override {
        // For a quadrilateral, the projection onto an axis is a line segment defined by
        // the projections of the quadrilateral's vertices onto the axis.
        float proj1 = glm::dot(glm::vec2(vertices[0].position), axis);
        float proj2 = glm::dot(glm::vec2(vertices[1].position), axis);
        float proj3 = glm::dot(glm::vec2(vertices[2].position), axis);
        float proj4 = glm::dot(glm::vec2(vertices[3].position), axis);
        return {std::min({proj1, proj2, proj3, proj4}), std::max({proj1, proj2, proj3, proj4})};
    }

private:
    int textureId;
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords;
    };

    Vertex vertices[6]; // 2 triangles, 3 vertices each
};

} // namespace RavenEngine