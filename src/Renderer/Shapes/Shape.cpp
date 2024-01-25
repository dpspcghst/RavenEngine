// Shape.cpp
#include "Shape.h"

namespace RavenEngine {

void Shape::SetPosition(const glm::vec3& position) {
    this->position = position;
}

void Shape::SetSize(const glm::vec3& size) {
    this->size = size;
}

void Shape::SetRotation(const glm::vec3& rotation) {
    this->rotation = rotation;
}

glm::vec3 Shape::GetPosition() const {
    return this->position;
}

glm::vec3 Shape::GetSize() const {
    return this->size;
}

glm::vec3 Shape::GetRotation() const {
    return this->rotation;
}

const std::string& Shape::GetShaderName() const {
    return shaderName;
}

} // namespace RavenEngine