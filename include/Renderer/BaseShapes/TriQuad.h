#pragma once

#include <glad/glad.h>

namespace RavenEngine {

class TriQuad {
public:
    TriQuad();
    ~TriQuad();

    void Create();
    void Render();

private:
    GLuint VAO, VBO;
};

} // namespace RavenEngine
