#pragma once
#include "SceneNode.h"
#include <vector>
#include <string>
#include <memory>
#include <set>

namespace RavenEngine {

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void AddNode(std::unique_ptr<SceneNode> node); 
    void RemoveNode(SceneNode* node);
    void Update(float deltaTime);
    SceneNode* FindNode(const std::string& name) const;
    void SetParent(SceneNode* child, SceneNode* parent);
    const std::vector<std::unique_ptr<SceneNode>>& GetNodes() const;
    std::vector<SceneNode*> GetAllNodes() const;

    int GetNextEntityID();

private:
    std::vector<std::unique_ptr<SceneNode>> nodes; 
    std::set<int> entityIDs;
};

} // namespace RavenEngine