// Triangle.h
#pragma once
// Standard library includes
// Third party includes
// Raven includes
#include "Shape2D.h"

namespace RavenEngine {

class Triangle : public Shape2D {
public:
    Triangle();
    virtual ~Triangle();

    // Override virtual functions from Shape2D
    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;
    int GetVertexCount() const override;
    int GetTextureId() const { return textureId; }
    void SetTextureId(int id) { textureId = id; }

private:
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords;
    };
    int textureId;

    Vertex vertices[3];
};

} // namespace RavenEngine