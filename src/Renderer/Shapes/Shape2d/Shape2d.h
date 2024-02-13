// shape2d.h
// #####################
#pragma once
// #include section
// #####################
// Standard library includes
#include <string>
#include <vector>
// Third party includes

// Raven includes
#include "../Shape.h"

namespace RavenEngine {

class Shape2D : public Shape {
public:
    enum class Type {
        Point,
        Line,
        Triangle,
        Rect,
        TriQuad,
        Circle,
    };

    static const std::vector<Type> AllTypes;

    Shape2D();
    explicit Shape2D(const glm::vec3& position, Type type);
    explicit Shape2D(const std::string& shaderName);

    ~Shape2D() override;

    // Inherited pure virtual functions
    virtual void Create() = 0;
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override = 0;
    glm::mat4 GetTransformMatrix() const override;

    void SetShaderName(const std::string& shaderName) override;

    // Shape-specific methods
    virtual int GetVertexCount() const = 0;
    Type GetSpecificType() const;
    static std::string GetTypeName(Type type);
    GLuint GetVAO() const;

    // Implement GetType from the base class to return ShapeType
    Shape::ShapeType GetType() const override;

    // Additional getters not present in the base class
    GLuint GetBindingPoint() const;

    void SetMaterialUBOName(const std::string& name) override;
    std::string GetMaterialUBOName() const override;

protected:
    void UpdateTransformMatrix();

    Type type;
    GLuint VAO;
};

} // namespace RavenEngine