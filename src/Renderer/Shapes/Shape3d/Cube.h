// Cube.h

#ifndef CUBE_H
#define CUBE_H

// Standard library includes
#include <array>

// Third party includes
#include <glm/glm.hpp>
#include <glad/glad.h>

// Raven includes
#include "Shape3D.h"

namespace RavenEngine {

class Cube : public Shape3D {
public:
    Cube(); // Default constructor
    Cube(GLuint shaderProgram); // Constructor with shaderProgram parameter
    ~Cube();

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;
    int GetVertexCount() const override;

private:
    GLuint VAO, VBO;
    GLuint shaderProgram;
    std::array<glm::vec3, 36> vertices;
};

} // namespace RavenEngine

#endif // CUBE_H