// scenemanager.cpp

// #include section
// #####################
// Standard library includes
#include <stack>
#include <iostream>

// Third party includes

// Raven includes
#include "SceneManager.h"
#include "../Renderer/Shapes/Shape.h"
#include "../Renderer/Shapes/Shape2d/Shape2d.h"
#include "../Renderer/Shapes/Shape3d/Shape3d.h"

namespace RavenEngine {

SceneManager::SceneManager() {
    rootNode = std::make_unique<SceneNode>();
    rootNode->SetName("rootNode");
}

SceneManager::~SceneManager() {                                                           // Destructor
    // no need to delete rootNode, as it is a unique_ptr
}
 
int SceneManager::GetNextEntityID() {                                                     // Get the next entity ID
    int newID = entityIDs.empty() ? 1 : *entityIDs.rbegin() + 1;
    return newID;
}

void SceneManager::AddNode(std::unique_ptr<SceneNode> node) {
    // ID assignment logic remains the same
    int newID;
    if (!deletedNodeIDs.empty()) {
        newID = deletedNodeIDs.top();
        deletedNodeIDs.pop();
        std::cout << "Reusing deleted node ID: " << newID << std::endl;
    } else {
        newID = GetNextEntityID();
        //std::cout << "Generated new node ID: " << newID << std::endl;
    }
    node->SetID(newID);
    entityIDs.insert(newID); // Add the entity ID to the set

    // Get the Shape associated with the node
    auto shapePtr = node->GetShape();
    if (shapePtr) {
        std::string shapeTypeName;

        // Attempt to dynamic_cast to Shape2D and Shape3D to get the specific type name
        if (auto shape2DPtr = dynamic_cast<Shape2D*>(shapePtr.get())) {
            shapeTypeName = Shape2D::GetTypeName(shape2DPtr->GetSpecificType());
        } else if (auto shape3DPtr = dynamic_cast<Shape3D*>(shapePtr.get())) {
            shapeTypeName = Shape3D::GetTypeName(shape3DPtr->GetSpecificType());
        } else {
            // Fallback for shapes that are neither 2D nor 3D
            shapeTypeName = "Unknown";
        }

        //std::cout << "SCENEMANAGER::ADDNODE Shape type: " << shapeTypeName << std::endl;

        std::string entityName = shapeTypeName + " " + std::to_string(newID);
        node->SetName(entityName);
        //std::cout << "SCENEMANAGER::ADDNODE Entity name set to: " << entityName << std::endl;
    } else {
        std::cout << "SCENEMANAGER::ADDNODE No shape associated with the node." << std::endl;
    }

    nodes.push_back(std::move(node)); // Add the node to the nodes vector
    rootNode->AddChild(nodes.back().get()); // Add the node to the root node
    //std::cout << "SCENEMANAGER::ADDNODE Node: " << nodes.back()->GetName() << " added to the scene." << std::endl;
}

void SceneManager::RemoveNode(SceneNode* node) {
    //std::cout << "SCENEMANAGER::REMOVENODE Removing node: " << node->GetName() << std::endl;
    deletedNodeIDs.push(node->GetID());
    entityIDs.erase(node->GetID());
    rootNode->RemoveChild(node);
}

std::vector<SceneNode*> SceneManager::GetAllNodes() const {                               
    std::vector<SceneNode*> allNodes;
    const auto& children = rootNode->GetChildren();  // Get the children of the rootNode
    for (const auto& child : children) {
        allNodes.push_back(child.get());
    }
    return allNodes;
}

const std::vector<std::unique_ptr<SceneNode>>& SceneManager::GetNodes() const {           // Get a reference to the vector of unique pointers to the nodes
    return nodes;
}

SceneNode& SceneManager::GetRootNode() const {                                            // Get the root node
    return *rootNode; // Dereference the unique_ptr
}

SceneNode* SceneManager::FindNode(const std::string& name) const {                        // Find a node by name
    for (const auto& node : nodes) { // Use const reference to avoid copying unique_ptr
        if (node && node->GetName() == name) {
            return node.get();
        }
    }
    return nullptr;
}

void SceneManager::SetParent(SceneNode* child, SceneNode* parent) {                       // Set the parent of a node
    // Ensure both child and parent are valid
    if (child && parent) {
        // Implement parent-child relationship
        // Update transforms, etc.
    }
}

void SceneManager::Update(float deltaTime) {                                              // Update the scene
    for (auto& node : nodes) { // Use reference to avoid copying unique_ptr
        if (node) { // Check if node is valid
            node->Update(deltaTime); // Update the node
        }
    }
}

} // namespace RavenEngine