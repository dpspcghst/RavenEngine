// scenenode.h
#ifndef RAVENENGINE_SCENENODE_H
#define RAVENENGINE_SCENENODE_H

// #include section
// #####################
// Standard library includes
#include <string>
#include <vector>
#include <memory>

// Third party includes

// Raven includes
#include "../Renderer/Shapes/Shape.h"  // Include the unified Shape.h

namespace RavenEngine {

class SceneNode {
public:
    SceneNode();  // Default constructor
    explicit SceneNode(const std::string& nodeName);  // Constructor that takes a name parameter
    ~SceneNode();

    void Update(float deltaTime);
    void AddChild(SceneNode* child);
    const std::vector<std::unique_ptr<SceneNode>>& GetChildren() const;
    void RemoveChild(const SceneNode* child);

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    void SetID(int newID);
    int GetID() const;

    void AttachShape(std::shared_ptr<Shape> newShape);  // Unified method to attach a shape

    std::shared_ptr<Shape> GetShape() const;  // Unified method to get the attached shape

private:
    std::string name;
    std::vector<std::unique_ptr<SceneNode>> children;
    int id;

    std::shared_ptr<Shape> shape;  // Unified shape member

};

} // namespace RavenEngine

#endif // RAVENENGINE_SCENENODE_H
