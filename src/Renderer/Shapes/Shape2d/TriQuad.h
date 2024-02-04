// TriQuad.h
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shape2d.h" // Include the Shape base class
#include "../../Shaders/ShaderManager.h" // Include the ShaderManager class

namespace RavenEngine {

class TriQuad : public Shape2D { // Make TriQuad inherit from Shape
public:
    TriQuad(); // Add a default constructor
    ~TriQuad();

    void Create() override; 
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;

    // Added getter method
    int GetVertexCount() const override { return 6; } // A TriQuad has 6 vertices

private:
    GLuint VAO;
    GLuint VBO;
    ShaderManager* shaderManager; // Add a ShaderManager reference
};

} // namespace RavenEngine