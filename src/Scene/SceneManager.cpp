#include "../Scene/SceneManager.h"

namespace RavenEngine {

SceneManager::SceneManager() {
    // Example of adding a node with a unique ID
    static int nextNodeId = 1;
    AddNode(std::make_unique<SceneNode>("InitialNode", nextNodeId++));
}

SceneManager::~SceneManager() {
    // Destructor logic
    // No need to manually delete nodes or clear the vector, unique_ptr will handle it
}

void SceneManager::AddNode(std::unique_ptr<SceneNode> node) {
    entityIDs.insert(node->GetID()); // Add this line
    nodes.push_back(std::move(node));
}

void SceneManager::RemoveNode(SceneNode* node) {
    entityIDs.erase(node->GetID()); // Add this line
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
        [node](const std::unique_ptr<SceneNode>& unique_ptr) {
            return unique_ptr.get() == node;
        }), nodes.end());
}

void SceneManager::Update(float deltaTime) {
    for (auto& node : nodes) { // Use reference to avoid copying unique_ptr
        if (node) {
            node->Update(deltaTime);
        }
    }
}

SceneNode* SceneManager::FindNode(const std::string& name) const {
    for (const auto& node : nodes) { // Use const reference to avoid copying unique_ptr
        if (node && node->GetName() == name) {
            return node.get();
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<SceneNode>>& SceneManager::GetNodes() const {
    return nodes;
}

std::vector<SceneNode*> SceneManager::GetAllNodes() const {
    std::vector<SceneNode*> allNodes;
    for (const auto& node : nodes) {
        allNodes.push_back(node.get());
    }
    return allNodes;
}

void SceneManager::SetParent(SceneNode* child, SceneNode* parent) {
    // Ensure both child and parent are valid
    if (child && parent) {
        // Implement parent-child relationship
        // Update transforms, etc.
    }
}

} // namespace RavenEngine