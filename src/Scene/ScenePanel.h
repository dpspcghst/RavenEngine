// scenepanel.h
#pragma once

// #include section
// #####################
// Standard library includes
#include <vector>

// Third party includes

// Local project includes
#include "SceneManager.h"
#include "SceneNode.h"
#include "../Renderer/Shaders/ShaderManager.h"
#include "../Renderer/Shapes/Shape.h" // Include the base Shape class

namespace RavenEngine {

class ScenePanel {
public:
    ScenePanel(ShaderManager& shaderManagerInstance); // Add ShaderManager reference to constructor
    void SetSceneManager(SceneManager* newSceneManager);
    void OnImGuiRender();

    void SetSize(int width, int height);
    void DrawNodeTree(SceneNode* node);
    
    void HandleNodeInteraction(SceneNode* node);
    void RemoveNode(SceneNode* node);
    
    void CreateShape(int shapeType, bool is3D = false); // Consolidated method for shape creation

    const std::vector<SceneNode*>& GetSelectedNodes() const;
    std::vector<SceneNode*> selectedNodes;

private:
    void DrawSceneNodes();

    ShaderManager& shaderManagerInstance; // Keep as a reference
    int width, height;

    SceneManager* sceneManager;

    void HandleNodeCreation(); // Node Creation Menu
    void HandleNodeDeletion(); // Node Removal
    void HandleNodeRenaming(); // Node Renaming
    void Handle2DShapeCreationMenu(); // Menu for creating 2D shapes
    void Handle3DShapeCreationMenu(); // Menu for creating 3D shapes
    bool renameRequested; // Flag to check if renaming is requested
    SceneNode* nodeToRename; // Member variable for node to rename
};

} // namespace RavenEngine
