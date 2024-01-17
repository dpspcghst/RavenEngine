#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../Maths/Vector3.h" // Make sure to include the header file for Vector3
#include "Renderer.h" // Include the header file for Renderer

namespace RavenEngine {

enum class ShapeType {
    Point,
    Line,
    Plane,
    // Add other shape types here
};

class SceneNode {
public:
    SceneNode(const std::string& name, int id); // Add id parameter to constructor
    ~SceneNode();

    void Update(float deltaTime);
    void AddChild(std::unique_ptr<SceneNode> child);
    void RemoveChild(const SceneNode* child);

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    const std::vector<std::unique_ptr<SceneNode>>& GetChildren() const;

    Vector3 GetPosition() const;
    void SetPosition(const Vector3& position);

    Vector3 GetRotation() const;
    void SetRotation(const Vector3& rotation);

    Vector3 GetScale() const;
    void SetScale(const Vector3& scale);

    int GetID() const;

    void AttachShape(ShapeType shapeType); // Attach a shape of a specific type to the node

    void SetRenderData(ShapeType type, const std::string& shaderName); // Set the render data
    void Render(Renderer& renderer); // Render the node

private:
    std::string name;
    std::vector<std::unique_ptr<SceneNode>> children;
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    int id; // Unique identifier for each node

    ShapeType shapeType; // The type of shape attached to the node
    std::string shaderName; // The name of the shader used to render the node
    // Other renderable data like VAO, VBO
};

} // namespace RavenEngine