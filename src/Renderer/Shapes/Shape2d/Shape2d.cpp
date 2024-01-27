// Shape2D.cpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shape2D.h"

namespace RavenEngine {

Shape2D::Shape2D() : VAO(0), VBO(0), size(1.0f, 1.0f, 0.0f), position(0.0f, 0.0f, 0.0f), rotation(0.0f), transformMatrix(1.0f) {
    UpdateTransformMatrix();
}

Shape2D::Shape2D(const glm::vec3& pos, Type type) : VAO(0), VBO(0), size(1.0f, 1.0f, 0.0f), position(pos), type(type), rotation(0.0f), transformMatrix(1.0f) {
    UpdateTransformMatrix();
}

Shape2D::Shape2D(const std::string& shaderName) : VAO(0), VBO(0), size(1.0f, 1.0f, 0.0f), position(0.0f, 0.0f, 0.0f), rotation(0.0f), transformMatrix(1.0f), shaderName(shaderName) {
    UpdateTransformMatrix();
}

Shape2D::~Shape2D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

Shape2D::Type Shape2D::GetType() const {
    return type;
}

std::string Shape2D::GetTypeName(Type type) {
    switch (type) {
        case Type::Point: return "Point";
        case Type::Line: return "Line";
        case Type::Triangle: return "Triangle";
        case Type::Plane: return "Plane";
        case Type::TriQuad: return "TriQuad";
        default: return "Unknown";
    }
}

glm::vec3 Shape2D::GetSize() const {
    return size;
}

void Shape2D::SetSize(const glm::vec3& newSize) {
    size = newSize;
    UpdateTransformMatrix();
}

glm::vec3 Shape2D::GetPosition() const {
    return position;
}

void Shape2D::SetPosition(const glm::vec3& newPosition) {
    position = newPosition;
    UpdateTransformMatrix();
}

glm::vec3 Shape2D::GetRotation() const {
    return rotation;
}

void Shape2D::SetRotation(const glm::vec3& newRotation) {
    rotation = newRotation;
    UpdateTransformMatrix();
}

void Shape2D::UpdateTransformMatrix() {
    // Start with an identity matrix
    transformMatrix = glm::mat4(1.0f);

    // Apply transformations: translate, then rotate, then scale
    transformMatrix = glm::translate(transformMatrix, position);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transformMatrix = glm::scale(transformMatrix, size);
}

void Shape2D::SetShaderName(const std::string& shaderName) {
    this->shaderName = shaderName;
}

const std::string& Shape2D::GetShaderName() const {
    return shaderName;
}

} // namespace RavenEngine