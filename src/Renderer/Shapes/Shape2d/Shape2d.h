// Shape2D.h
#pragma once

// Standard library includes
#include <string>

// Third party includes
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace RavenEngine {

class Shape2D {
public:
    enum class Type {
        Point,
        Line,
        Triangle,
        Plane,
        TriQuad,
        Circle,
    };

    Shape2D();
    Shape2D(const glm::vec3& position, Type type);
    Shape2D(const std::string& shaderName);

    virtual ~Shape2D();

    virtual int GetVertexCount() const = 0;

    virtual void Create() = 0;
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const = 0;

    void SetSize(const glm::vec3& size);
    void SetPosition(const glm::vec3& position);
    void SetRotation(const glm::vec3& rotation);

    glm::vec3 GetSize() const;
    glm::vec3 GetPosition() const;
    glm::vec3 GetRotation() const;

    glm::mat4 GetTransformMatrix() const {
        return transformMatrix;
    }
    
    Type GetType() const;
    static std::string GetTypeName(Type type);
    GLuint GetVAO() const;

    // Declare methods to set and get the shader name
    void SetShaderName(const std::string& shaderName);
    const std::string& GetShaderName() const;

protected:
    void UpdateTransformMatrix();

    glm::mat4 transformMatrix;
    glm::vec3 size;
    glm::vec3 position;
    glm::vec3 rotation;
    GLuint VAO, VBO;
    Type type;

    std::string shaderName;
};

} // namespace RavenEngine