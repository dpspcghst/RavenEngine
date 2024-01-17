// Shape.cpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../../include/Renderer/BaseShapes/Shape.h"

namespace RavenEngine {

Shape::Shape() : VAO(0), VBO(0), size(1.0f), position(0.0f) {
    UpdateTransformMatrix();
}

void Shape::SetSize(const glm::vec3& newSize) {
    size = newSize;
    UpdateTransformMatrix();
}

void Shape::SetPosition(const glm::vec3& newPosition) {
    position = newPosition;
    UpdateTransformMatrix();
}

glm::vec3 Shape::GetSize() const {
    return size;
}

void Shape::UpdateTransformMatrix() {
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, position);
    transformMatrix = glm::scale(transformMatrix, size);
}

} // namespace RavenEngine