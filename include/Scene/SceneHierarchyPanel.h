#pragma once
#include "SceneManager.h"
#include "SceneNode.h" // Include this to get the ShapeType enum
#include <vector>

namespace RavenEngine {

class SceneHierarchyPanel {
public:
    SceneHierarchyPanel();
    void SetContext(SceneManager* newContext);
    void OnImGuiRender();
    void DrawNodeTree(SceneNode* node);
    void HandleNodeInteraction(SceneNode* node);
    void RemoveNode(SceneNode* node);

    template<ShapeType shapeType>
    void CreateShape();

    std::vector<SceneNode*> selectedNodes;

private:
    SceneManager* context;
    SceneNode* nodeToRename; // Member variable for node to rename
    bool renameRequested; // Flag to indicate renaming is requested
};

} // namespace RavenEngine