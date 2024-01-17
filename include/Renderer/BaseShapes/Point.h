#pragma once

#include <glm/glm.hpp>
#include "../../../Assets/Shaders/ShaderManager.h"
#include "Shape.h"

namespace RavenEngine {

class Point : public Shape {
public:
    Point(const glm::vec3& position);
    ~Point();

    void Create() override;
    void Render(ShaderManager& shaderManager, const std::string& shaderName, const glm::mat4& projectionMatrix) override;
};

} // namespace RavenEngine