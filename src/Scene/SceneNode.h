// scenenode.h
#pragma once
// #include section
// #####################
// Standard library includes
#include <string>
#include <vector>
#include <memory>

// Third party includes

// Raven includes
#include "../Renderer/Shapes/Shape.h"
#include "../Renderer/Shapes/Shape2D/Shape2D.h"

namespace RavenEngine {

class SceneNode {
public:
    SceneNode();
    ~SceneNode();

    void Update(float deltaTime);
    void AddChild(std::unique_ptr<SceneNode> child);
    const std::vector<std::unique_ptr<SceneNode>>& GetChildren() const;
    void RemoveChild(const SceneNode* child);

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    void SetID(int newID);
    int GetID() const;

    void AttachShape(std::shared_ptr<Shape> shape);

    std::shared_ptr<Shape> GetShape() const; // Changed return type to std::shared_ptr<Shape>
private:
    std::string name;
    std::vector<std::unique_ptr<SceneNode>> children;
    int id;

    std::shared_ptr<Shape> shape;

};

} // namespace RavenEngine