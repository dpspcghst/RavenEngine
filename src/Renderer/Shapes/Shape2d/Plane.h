// Plane.h
#pragma once

#include <glad/glad.h>
#include "Shape2d.h"

namespace RavenEngine {

class Plane : public Shape2D {
public:
    Plane(); // Default constructor
    ~Plane();

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;

    // Added getter method
    int GetVertexCount() const override { return 4; } // A plane has 4 vertices

private:
    GLuint VAO, VBO;
};

} // namespace RavenEngine