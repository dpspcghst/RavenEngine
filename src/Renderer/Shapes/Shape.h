// Shape.h
#pragma once

// #include section
// #####################

// Standard library includes
#include <glm/glm.hpp>
#include <memory>
#include <string>

namespace RavenEngine {

class Shape {
public:
    virtual ~Shape() = default;

    virtual void SetPosition(const glm::vec3& position);
    virtual void SetSize(const glm::vec3& size);
    virtual void SetRotation(const glm::vec3& rotation);

    virtual glm::vec3 GetPosition() const;
    virtual glm::vec3 GetSize() const;
    virtual glm::vec3 GetRotation() const;

    virtual void Render() const = 0;

    // Add a method to get the shader name
    virtual const std::string& GetShaderName() const;
    virtual glm::mat4 GetTransformMatrix() const = 0;


protected:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotation;

    // Add a member variable to store the shader name
    std::string shaderName;
};

using ShapePtr = std::shared_ptr<Shape>;

} // namespace RavenEngine