// shape.h
#pragma once

// #include section
// #####################
// Standard library includes
#include <string>
// Third party includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// Raven includes
#include "../Shaders/ShaderManager.h"
#include "../Materials/MaterialProperties.h"
#include "../Materials/MaterialProperties3D.h"

namespace RavenEngine {
class Shape {
public:
    static int nextID;

    enum class ShapeType {
        Shape2D,
        Shape3D,
    };
    // Default constructor
    Shape() : shaderName(""), shaderProgram(0), ID(0), materialUBOName(""), color(glm::vec4(1.0f)), 
              size(glm::vec3(1.0f)), position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), 
              VAO(0), VBO(0), ubo(0), bindingPoint(0), transformMatrix(glm::mat4(1.0f)) {
        // Initialize other members as needed.
    }

    // Constructor that accepts a shader name
    Shape(const std::string& shaderName) : Shape() { // Use delegating constructor (C++11)
        SetShaderName(shaderName);
    }

    virtual ~Shape() = default;

    virtual void Create() = 0; 
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const = 0; 

    virtual void SetShaderName(const std::string& shaderName);
    virtual const std::string& GetShaderName() const;

    virtual void SetID(int id);
    virtual int GetID() const;

    virtual void SetMaterialUBOName(const std::string& name);
    virtual std::string GetMaterialUBOName() const;

    virtual void SetColor(const glm::vec4& newColor);
    virtual glm::vec4 GetColor() const;

    virtual void SetSize(const glm::vec3& newSize);
    virtual glm::vec3 GetSize() const;

    virtual void SetPosition(const glm::vec3& newPosition);
    virtual glm::vec3 GetPosition() const;

    virtual void SetRotation(const glm::vec3& newRotation);
    virtual glm::vec3 GetRotation() const;

    virtual glm::mat4 GetTransformMatrix() const = 0;
    virtual void UpdateTransformMatrix() {
        transformMatrix = glm::mat4(1.0f);
        transformMatrix = glm::translate(transformMatrix, position);
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transformMatrix = glm::scale(transformMatrix, size);
    }
    virtual ShapeType GetType() const = 0;

protected:
    std::string shaderName;
    GLuint shaderProgram;
    int ID;
    std::string materialUBOName;
    glm::vec4 color;
    glm::vec3 size;
    glm::vec3 position;
    glm::vec3 rotation;
    GLuint VAO, VBO, ubo;
    GLuint bindingPoint;
    glm::mat4 transformMatrix;
};

} // namespace RavenEngine