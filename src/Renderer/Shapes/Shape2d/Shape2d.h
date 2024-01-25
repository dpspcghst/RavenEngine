// Shape2D.h
#pragma once

// Standard library includes
#include <string>

// Third party includes
#include <glad/glad.h>
#include <glm/glm.hpp>

// Local includes
#include "../Shape.h"

namespace RavenEngine {

class Shape2D : public Shape {
public:
    enum class Type {
        Point,
        Line,
        Triangle,
        Plane,
        TriQuad
    };

    Shape2D();
    Shape2D(const glm::vec3& position, Type type);
    virtual ~Shape2D();

    virtual int GetVertexCount() const = 0;

    virtual void Create() = 0;
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const = 0;

    void SetSize(const glm::vec3& size) override;
    void SetPosition(const glm::vec3& position) override;
    void SetRotation(const glm::vec3& rotation) override;

    glm::vec3 GetSize() const override;
    glm::vec3 GetPosition() const override;
    glm::vec3 GetRotation() const override;

    glm::mat4 GetTransformMatrix() const override {
    return transformMatrix;
    }
    
    Type GetType() const;
    static std::string GetTypeName(Type type);
    GLuint GetVAO() const;

protected:
    void UpdateTransformMatrix();

    glm::mat4 transformMatrix;
    glm::vec3 size;
    glm::vec3 position;
    glm::vec3 rotation;
    GLuint VAO, VBO;
    Type type;
};

} // namespace RavenEngine