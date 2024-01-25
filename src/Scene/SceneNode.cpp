// scenenode.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
#include <algorithm>

// Third party includes
#include <glm/gtx/string_cast.hpp>

// Local project includes
#include "SceneNode.h"
#include "../Renderer/Shapes/Shape2D/Point.h"
#include "../Renderer/Shapes/Shape2D/Line.h"
#include "../Renderer/Shapes/Shape2D/Plane.h"
#include "../Renderer/Shapes/Shape2D/Triangle.h"
#include "../Renderer/Shapes/Shape2D/TriQuad.h"
#include "../../Assets/Shaders/ShaderManager.h"

namespace RavenEngine {

SceneNode::SceneNode() {
    // Constructor definition
    // Currently empty...
}

SceneNode::~SceneNode() {                                                                                        // Destructor
    //std::cout << "SceneNode destructor called" << std::endl;
}

void SceneNode::Update(float deltaTime) {                                                                        // Update method
    for (auto& child : children) {
        child->Update(deltaTime);
    }
}

void SceneNode::AddChild(std::unique_ptr<SceneNode> child) {                                                     // Add child method
    children.push_back(std::move(child));
}

const std::vector<std::unique_ptr<SceneNode>>& SceneNode::GetChildren() const {                                  // Get children method
    return children;
}

void SceneNode::RemoveChild(const SceneNode* child) {
    std::cout << "Removing child: " << child->GetName() << std::endl;  // Add this line
    children.erase(std::remove_if(children.begin(), children.end(),
                                  [child](const std::unique_ptr<SceneNode>& c) { return c.get() == child; }),
                   children.end());
}

const std::string& SceneNode::GetName() const {                                                                  // Get node name method
    return name;
}

void SceneNode::SetName(const std::string& newName) {                                                            // Set node name method
    name = newName;
}

void SceneNode::AttachShape(std::shared_ptr<Shape> newShape) {
    shape = std::move(newShape);
}

std::shared_ptr<Shape> SceneNode::GetShape() const {
    return shape;
}

void SceneNode::SetID(int newID) {
    id = newID;
}

int SceneNode::GetID() const {                                                                                   // Get ID method
    return id;
}

} // namespace RavenEngine