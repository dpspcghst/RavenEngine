#pragma once

#include <string>
#include <vector>
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

    // Inherited pure virtual functions implemented in Shape2D.cpp
    virtual void Create() = 0;
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override = 0;
    glm::mat4 GetTransformMatrix() const {
        return transformMatrix;
    }

    void SetShaderName(const std::string& shaderName) override;

    // Shape-specific methods
    virtual int GetVertexCount() const = 0;
    Type GetSpecificType() const; // Rename from GetType to GetSpecificType
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

    Type type;  // Specific to Shape2D
    GLuint VAO;  // OpenGL Vertex Array Object, specific to Shape2D
};

} // namespace RavenEngine
