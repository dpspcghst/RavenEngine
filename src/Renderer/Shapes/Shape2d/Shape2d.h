// shape2d.h
// #####################
#pragma once
// #include section
// #####################
// Standard library includes
#include <string>
#include <vector>
#include <memory>
// Third party includes

// Raven includes
#include "../Shape.h"
#include "../../../Physics/RigidBody.h"

namespace RavenEngine {

class RigidBody;
    
class Shape2D : public Shape, public std::enable_shared_from_this<Shape2D> {
public:
    enum class Type {
        Point,
        Line,
        Triangle,
        Rect,
        TriQuad,
        Circle,
    };

    enum class BodyType {
        Static,
        Dynamic,
        Kinematic
    };

    struct Projection {
        float min;
        float max;
    };

    static const std::vector<Type> AllTypes;

    Shape2D();
    explicit Shape2D(const glm::vec3& position, Type type, BodyType bodyType = BodyType::Static);
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

    void SetBodyType(BodyType newBodyType) { this->bodyType = newBodyType; }
    BodyType GetBodyType() const { return this->bodyType; }
    
    virtual std::vector<glm::vec3> GetVertices() const = 0;
    virtual std::vector<glm::vec2> GetNormals() const = 0;

    virtual Projection ProjectOntoAxis(const glm::vec2& axis) const = 0;

    void SetCollisionEnabled(bool enabled);
    bool IsCollisionEnabled() const;

    std::shared_ptr<RigidBody> GetRigidBody() const;

protected:
    void UpdateTransformMatrix();
    bool collisionEnabled = false;
    BodyType bodyType = BodyType::Static;

    Type type;
    GLuint VAO;

    std::shared_ptr<RigidBody> rigidBody;
};

} // namespace RavenEngine