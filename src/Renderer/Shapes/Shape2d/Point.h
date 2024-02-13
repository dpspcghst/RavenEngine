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

private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords; // Default texture coordinates, unused for Point
    };

    Vertex vertex;
};

} // namespace RavenEngine