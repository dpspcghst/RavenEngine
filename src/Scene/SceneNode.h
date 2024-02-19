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
#include <glm/glm.hpp> 

// Raven includes
#include "../Renderer/Shapes/Shape.h"

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

    void AttachShape(std::shared_ptr<Shape> newShape, int textureId);  // Change this line  // Unified method to attach a shape and set its texture ID

    std::shared_ptr<Shape> GetShape() const;  // Unified method to get the attached shape

    void SetTextureId(const std::string& newTextureId) { textureId = newTextureId; }
    const std::string& GetTextureId() const { return textureId; }

    const glm::mat4& GetTransformMatrix() const { return transformMatrix; }  // Getter for the transformation matrix

    // New method to check if this node is open in a tab
    bool IsOpenInTab() const { return isOpenInTab; }

    // New method to set whether this node is open in a tab
    void SetOpenInTab(bool open) { isOpenInTab = open; }

private:
    std::string name;
    std::vector<std::unique_ptr<SceneNode>> children;
    int id;

    std::shared_ptr<Shape> shape;  // Unified shape member

    std::string textureId;

    glm::mat4 transformMatrix;  // Transformation matrix member

    bool isOpenInTab = false;

};

} // namespace RavenEngine

#endif // RAVENENGINE_SCENENODE_H