// Line.h
#pragma once

#include <glm/glm.hpp>
#include "Shape.h" // Include the Shape base class

namespace RavenEngine {

class Line : public Shape { // Make Line inherit from Shape
public:
    Line(const glm::vec3& startPoint, const glm::vec3& endPoint);
    ~Line();

    void Create() override; // Override the Create method from Shape
    void Render(ShaderManager& shaderManager, const std::string& shaderName);

private:
    glm::vec3 start;
    glm::vec3 end;
};

} // namespace RavenEngine