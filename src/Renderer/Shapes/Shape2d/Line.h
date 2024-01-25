#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shape2D.h"

namespace RavenEngine {

class Line : public Shape2D {
public:
    Line() = default;
    Line(const glm::vec2& startPoint, const glm::vec2& endPoint);
    ~Line();

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override; // From Shape2D

    void Render() const override {
        // Provide an implementation here, or leave empty if not applicable
    }

    int GetVertexCount() const override { return 2; }

private:
    glm::vec2 start, end;
    GLuint VAO, VBO;
};

} // namespace RavenEngine
