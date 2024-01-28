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
#include "../Renderer/Shapes/Shape2D/Circle.h"
#include "../../Assets/Shaders/ShaderManager.h"

namespace RavenEngine {

SceneNode::SceneNode() : name("") {
    // Default constructor
}

SceneNode::SceneNode(const std::string& nodeName) : name(nodeName) {
    name = nodeName;
}

SceneNode::~SceneNode() {                                                                                        // Destructor
    //std::cout << "SceneNode destructor called" << std::endl;
}

void SceneNode::Update(float deltaTime) {                                                                        // Update method
    for (auto& child : children) {
        child->Update(deltaTime);
    }
}

void SceneNode::AddChild(SceneNode* child) {
    children.push_back(std::unique_ptr<SceneNode>(child));
    
    // Debugging information
    //std::cout << "Address of this SceneNode: " << this << std::endl;
    //std::cout << "Added child to node. Total children: " << children.size() << std::endl;
}

const std::vector<std::unique_ptr<SceneNode>>& SceneNode::GetChildren() const {                                  // Get children method
    return children;
}

void SceneNode::RemoveChild(const SceneNode* child) {
    //std::cout << "Removing child: " << child->GetName() << " from node: " << GetName() << std::endl;
    children.erase(std::remove_if(children.begin(), children.end(),
                                  [child](const std::unique_ptr<SceneNode>& c) { return c.get() == child; }),
                   children.end());

    //std::cout << "Total children: " << children.size() << std::endl;
}

const std::string& SceneNode::GetName() const {                                                                  // Get node name method
    return name;
}

void SceneNode::SetName(const std::string& newName) {                                                            // Set node name method
    name = newName;
}

void SceneNode::AttachShape(std::shared_ptr<Shape2D> newShape) {
    if (!newShape) {
        //std::cout << "Error: Attempted to attach a null shape to node: " << GetName() << std::endl;
        return;
    }

    //std::cout << "Attaching shape to node: " << GetName() << std::endl;
    shape = std::move(newShape);
}

std::shared_ptr<Shape2D> SceneNode::GetShape() const {
    if (shape) {
        //std::cout << "Retrieving shape from node: " << GetName() << std::endl;
    } else {
        //std::cout << "No shape attached to node: " << GetName() << std::endl;
    }
    return shape;
}

void SceneNode::SetID(int newID) {
    id = newID;
}

int SceneNode::GetID() const {                                                                                   // Get ID method
    return id;
}

} // namespace RavenEngine