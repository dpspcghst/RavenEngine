// scenemanager.cpp

// #include section
// #####################
// Standard library includes
#include <stack>
#include <iostream>

// Third party includes

// Raven includes
#include "SceneManager.h"
#include "../Renderer/Shapes/Shape2D/Shape2D.h"

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
    int newID;
    if (!deletedNodeIDs.empty()) {
        newID = deletedNodeIDs.top();
        deletedNodeIDs.pop();
    } else {
        newID = GetNextEntityID();
    }
    node->SetID(newID);
    entityIDs.insert(newID); // Add the entity ID to the set

    // Get the raw pointer from the shared_ptr and cast it to Shape2D*
    auto shapePtr = node->GetShape();
    if (shapePtr) {
        Shape2D* shape2D = dynamic_cast<Shape2D*>(shapePtr.get());
        if (shape2D) {
            // Use the Shape2D class instead of the Shape class
            Shape2D::Type shapeType = shape2D->GetType();
            std::string shapeTypeName = Shape2D::GetTypeName(shapeType);
            std::string entityName = shapeTypeName + " " + std::to_string(newID);
            node->SetName(entityName);
        }
    }

    nodes.push_back(std::move(node)); // Add the node to the nodes vector
    rootNode->AddChild(nodes.back().get()); // Add the node to the root node

    // Debugging information
    std::cout << "Address of rootNode: " << rootNode.get() << std::endl;
    std::cout << "Child count of rootNode: " << rootNode->GetChildren().size() << std::endl;

    std::cout << "Added node to root node. Total children in root node: " << rootNode->GetChildren().size() << std::endl;
    std::cout << "Total nodes: " << nodes.size() << std::endl;
}

void SceneManager::RemoveNode(SceneNode* node) {
    std::cout << "Removing node: " << node->GetName() << std::endl;
    deletedNodeIDs.push(node->GetID());
    entityIDs.erase(node->GetID());
    rootNode->RemoveChild(node);


    // // Remove the node from the nodes vector
    // nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
    //                            [node](const std::unique_ptr<SceneNode>& n) { return n.get() == node; }),
    //             nodes.end());

    // Debug print statements
    std::cout << "deletedNodeIDs size: " << deletedNodeIDs.size() << std::endl;
    std::cout << "nodes size: " << nodes.size() << std::endl;
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