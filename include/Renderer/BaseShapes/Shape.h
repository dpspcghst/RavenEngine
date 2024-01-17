#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "../../../Assets/Shaders/ShaderManager.h"

namespace RavenEngine {

class Shape {
public:
    Shape();
    Shape(const glm::vec3& position); // New constructor
    virtual ~Shape() {}
    virtual void Create() = 0;
    virtual void Render(ShaderManager& shaderManager, const std::string& shaderName, const glm::mat4& projectionMatrix) = 0;
    void SetSize(const glm::vec3& size); // Updated to use glm::vec3
    void SetPosition(const glm::vec3& position);
    glm::vec3 GetSize() const; // Updated to return glm::vec3

protected:
    void UpdateTransformMatrix();

    glm::mat4 transformMatrix;
    glm::vec3 size; // Updated to use glm::vec3
    glm::vec3 position;
    GLuint VAO, VBO;
};

} // namespace RavenEngine