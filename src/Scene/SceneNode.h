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
#include "../Renderer/Shapes/Shape2D/Shape2D.h"

namespace RavenEngine {

class SceneNode {
public:
    SceneNode();  // Default constructor
    SceneNode(const std::string& nodeName);  // Constructor that takes a name parameter
    ~SceneNode();

    void Update(float deltaTime);
    void AddChild(SceneNode* child);
    const std::vector<std::unique_ptr<SceneNode>>& GetChildren() const;
    void RemoveChild(const SceneNode* child);

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    void SetID(int newID);
    int GetID() const;

    void AttachShape(std::shared_ptr<Shape2D> shape);

    std::shared_ptr<Shape2D> GetShape() const; // Changed return type to std::shared_ptr<Shape>
private:
    std::string name;
    std::vector<std::unique_ptr<SceneNode>> children;
    int id;

    std::shared_ptr<Shape2D> shape;

};

} // namespace RavenEngine