#pragma once

#include <glm/glm.hpp>
#include "../../../Assets/Shaders/ShaderManager.h"
#include "Shape2D.h"

namespace RavenEngine {

class Point : public Shape2D {
public:
    Point() = default;
    Point(const glm::vec3& position);
    ~Point();

    void Create() override;

    // Implement the Render method from Shape2D
    void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;

    int GetVertexCount() const override { return 1; }

};

} // namespace RavenEngine