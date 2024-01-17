#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace RavenEngine {

class Triangle {
public:
    Triangle();
    ~Triangle();

    void Create(); // Set up the triangle data
    void Render(); // Render the triangle

private:
    GLuint VAO;
    GLuint VBO;
};

} // namespace RavenEngine
