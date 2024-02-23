// Inspector.h
// ####################
#ifndef INSPECTOR_H
#define INSPECTOR_H
// ####################
// #include section
// ####################
// Standard library includes
#include <unordered_map>
// Third-party library includes
#include <imgui.h>
// Raven includes
#include "../../src/Scene/ScenePanel.h"
#include "../../src/Scene/SceneNode.h"
#include "../../src/Renderer/Shapes/Shape2D/Shape2D.h"
#include "../../src/Renderer/Shapes/Shape3D/Shape3D.h"
#include "../../src/Renderer/Texture/TexturePanel.h"
#include "../../src/Renderer/Texture/TextureManager.h"
#include "../../src/Physics/CollisionPanel.h"
#include "../../src/Physics/GravityManager.h"
#include "../../src/Physics/GravityPanel.h"

namespace RavenEngine {

class SceneManager; // Forward declaration of SceneManager

class Inspector {
public:
    Inspector(ScenePanel& scenePanel, TextureManager& textureManager, CollisionPanel& collisionPanel, SceneManager* sceneManager); // Add TextureManager to constructor

    void Render();
    

private:
    ScenePanel& scenePanel; // Reference to ScenePanel
    SceneManager* sceneManager; // Add SceneManager member
    TexturePanel texturePanel; // Add TexturePanel member
    CollisionPanel& collisionPanel; // Add CollisionPanel member
    GravityManager gravityManager; // Add GravityManager member
    std::unique_ptr<GravityPanel> gravityPanel;

    SceneNode* lastSelectedNode = nullptr;

    void RenderShapeDetails(Shape* shape, SceneNode* selectedNode);
    void RenderCommonShapeProperties(Shape* shape);
    void RenderShape2DDetails(Shape2D* shape2D);
    void RenderShape3DDetails(Shape3D* shape3D);

    void OnTextureLoaded(int textureId);

    void RenderTabs();
    void RenderExistingTabs();
    void RenderTab(SceneNode* node, std::vector<int>& toClose);
    void CloseTabs(std::vector<int>& toClose);
    void AddNewTabs();

    std::unordered_map<int, bool> openTabs;

    void RenderNodeProperties(SceneNode* selectedNode);
    
};

} // namespace RavenEngine

#endif // INSPECTOR_H