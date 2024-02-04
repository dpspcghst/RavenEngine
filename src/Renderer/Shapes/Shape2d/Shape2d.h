// Shape2D.h
#pragma once

// Standard library includes
#include <string>

// Raven includes
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace RavenEngine {

class Shape2D {
public:
    enum class Type {
        Point,
        Line,
        Triangle,
        Rect,
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

    void SetColor(const glm::vec4& newColor);
    glm::vec4 GetColor() const;

    void SetMaterialUBOName(const std::string& name);
    std::string GetMaterialUBOName() const;
    
    Type GetType() const;
    static std::string GetTypeName(Type type);
    GLuint GetVAO() const;

    void SetShaderName(const std::string& shaderName);
    const std::string& GetShaderName() const;

    void SetID(int newID); // Use int for ID
    int GetID() const; // Use int for ID
    GLuint GetBindingPoint() const;


protected:
    void UpdateTransformMatrix();

    glm::mat4 transformMatrix;
    glm::vec3 size;
    glm::vec3 position;
    glm::vec3 rotation;
    GLuint VAO, VBO;
    Type type;
    glm::vec4 color; // Color property for the shape

    std::string shaderName; // Name of the shader used for this shape
    std::string materialUBOName;

    GLuint shaderProgram; // ID of the shader program used for this shape
    GLuint ubo;
    int ID; // ID of the shape
    static int nextID; // Static variable to keep track of the next ID to be assigned
    GLuint bindingPoint; // UBO binding point for this shape

};

} // namespace RavenEngine