// Triangle.h
#pragma once

// #include section
// #####################
// Standard library includes

// Third party includes
#include <glm/glm.hpp>

// Raven includes
#include "Shape2d.h"

namespace RavenEngine { 

class Triangle : public Shape2D {
public:
    Triangle();
    Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
    ~Triangle();

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;

    // Implement the Render method from Shape (if needed)
    void Render() const override {
        // Provide an implementation here, or leave empty if not applicable
    }

    // Added getter method
    int GetVertexCount() const override { return 3; } // A triangle has 3 vertices

private:
    glm::vec3 vertices[3];
};

} // namespace RavenEngine