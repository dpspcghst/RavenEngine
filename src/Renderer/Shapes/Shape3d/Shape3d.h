
#pragma once

#include <string>
#include <vector>
#include "../Shape.h"

namespace RavenEngine {

class Shape3D : public Shape {
public:
    enum class Type {
        Cube,
        Sphere,
        Cylinder,
        Cone,
        Pyramid,
        Torus,
        Custom,
    };

    static const std::vector<Type> AllTypes;

    Shape3D();
    Shape3D(const glm::vec3& position, Type type);
    Shape3D(const std::string& shaderName);

    virtual ~Shape3D();

    void SetShaderName(const std::string& shaderName) override;

    virtual int GetVertexCount() const = 0;

    virtual void Create() = 0;
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override = 0;

    glm::mat4 GetTransformMatrix() const override;

    // Type-specific methods
    Type GetSpecificType() const; // Rename from GetType to GetSpecificType
    static std::string GetTypeName(Type type);
    GLuint GetVAO() const;

    // Implement GetType from the base class to return ShapeType
    ShapeType GetType() const override;

    GLuint GetBindingPoint() const;

protected:
    void UpdateTransformMatrix();

    Type type;
    GLuint VAO, VBO;
};

} // namespace RavenEngine
