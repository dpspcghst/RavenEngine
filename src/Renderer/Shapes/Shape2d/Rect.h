// Rect.h
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

class Rect : public Shape2D {
public:
    Rect();
    virtual ~Rect();

    void Create() override;
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;
    
    int GetVertexCount() const override;

    int GetTextureId() const { return textureId; }
    void SetTextureId(int id) { textureId = id; }

private:
    int textureId;
    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords;
    };

    Vertex vertices[4]; // Define four vertices for a rectangle
};

} // namespace RavenEngine