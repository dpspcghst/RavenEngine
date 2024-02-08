#include "SceneNode.h"
// #include section
// #####################
// Standard library includes
#include <iostream>
#include <algorithm>

// Third party includes
#include <glm/gtx/string_cast.hpp>

// Local project includes
#include "../Renderer/Shapes/Shape.h"  // Include the unified Shape.h
#include "../Renderer/Shaders/ShaderManager.h"

namespace RavenEngine {

SceneNode::SceneNode() : name("") {
    // Default constructor
}

SceneNode::SceneNode(const std::string& nodeName) : name(nodeName) {
    // Constructor
}

SceneNode::~SceneNode() {
    // Destructor
}

void SceneNode::Update(float deltaTime) {
    for (auto& child : children) {
        child->Update(deltaTime);
    }
}

void SceneNode::AddChild(SceneNode* child) {
    children.push_back(std::unique_ptr<SceneNode>(child));
}

const std::vector<std::unique_ptr<SceneNode>>& SceneNode::GetChildren() const {
    return children;
}

void SceneNode::RemoveChild(const SceneNode* child) {
    children.erase(std::remove_if(children.begin(), children.end(),
                                  [child](const std::unique_ptr<SceneNode>& c) { return c.get() == child; }),
                   children.end());
}

const std::string& SceneNode::GetName() const {
    return name;
}

void SceneNode::SetName(const std::string& newName) {
    name = newName;
}

void SceneNode::AttachShape(std::shared_ptr<Shape> newShape) { 
    if (!newShape) {
        std::cout << "Attempted to attach a null shape to node: " << this->GetName() << std::endl;
        return;
    }
    shape = std::move(newShape);
    std::cout << "SCENENODE::ATTACHSHAPE Attached shape to node: " << this->GetName() << std::endl;
}

std::shared_ptr<Shape> SceneNode::GetShape() const { 
    return shape;
}

void SceneNode::SetID(int newID) {
    id = newID;
}

int SceneNode::GetID() const {
    return id;
}

} // namespace RavenEngine
