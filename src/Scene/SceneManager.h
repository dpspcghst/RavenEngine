// scenemanager.h
#pragma once

// #include section
// #####################
// Standard library includes
#include <vector>
#include <string>
#include <memory>
#include <set>
#include <stack>  // Add this line
// Third party includes

// Raven includes
#include "SceneNode.h"

namespace RavenEngine {

class SceneManager {
public:
    SceneManager(); // Constructor that takes a reference to a ShaderManager
    ~SceneManager(); // Destructor

    int GetNextEntityID(); // Returns the next entity ID

    void AddNode(std::unique_ptr<SceneNode> node); // Adds a node to the scene
    void RemoveNode(SceneNode* node); // Removes a node from the scene

    void Update(float deltaTime); // Updates the scene

    SceneNode& GetRootNode() const; // Returns a reference to the root node
    SceneNode* GetRootNodePtr() const {
    return rootNode.get();
    }
    
    const std::vector<std::unique_ptr<SceneNode>>& GetNodes() const; // Returns a reference to the vector of unique pointers to the nodes
    std::vector<SceneNode*> GetAllNodes() const; // Returns a vector of raw pointers to all nodes in the scene
    
    SceneNode* FindNode(const std::string& name) const; // Finds a node by name
    SceneNode* FindNodeById(int id) const {
        for (const auto& node : nodes) {
            if (node->GetID() == id) {
                return node.get();
            }
        }
        // Optionally, also check the rootNode if it can have an ID and be searched
        if (rootNode && rootNode->GetID() == id) {
            return rootNode.get();
        }
        return nullptr; // Return nullptr if no matching node is found
    }
    
    void SetParent(SceneNode* child, SceneNode* parent); // Sets the parent of a node

private:
    std::vector<std::unique_ptr<SceneNode>> nodes; // Vector of unique pointers to the nodes
    std::unique_ptr<SceneNode> rootNode; // Unique pointer to the root node
    std::set<int> entityIDs; // Set of entity IDs
    std::stack<int> deletedNodeIDs;  // Add this line

};

} // namespace RavenEngine