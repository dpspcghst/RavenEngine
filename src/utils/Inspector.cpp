// Inspector.cpp

// #include section
// #################
// Standard library includes
#include <iostream>
// Third-party library includes
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
// Raven includes
#include "Inspector.h"
#include "../Scene/SceneManager.h"
#include "../Scene/ScenePanel.h"
#include "../Scene/SceneNode.h"
#include "../Renderer/Shapes/Shape2D/Shape2D.h"
#include "../Renderer/Shapes/Shape3D/Shape3D.h"
#include "../Renderer/Texture/TexturePanel.h"
#include "../Physics/CollisionPanel.h"
#include "../Physics/RigidBodyPanel.h"

namespace RavenEngine {

Inspector::Inspector(ScenePanel& scenePanel, TextureManager& textureManager, CollisionPanel& collisionPanel, SceneManager* sceneManager)
: scenePanel(scenePanel), texturePanel(textureManager, [this](int textureId) { this->OnTextureLoaded(textureId); }), collisionPanel(collisionPanel), sceneManager(sceneManager) {
}

void Inspector::RenderShapeDetails(Shape* shape, SceneNode* selectedNode) {
    const int MAX_NAME_LENGTH = 128;
    std::string name = selectedNode->GetName();
    std::string inputId = "##NameInput" + std::to_string(selectedNode->GetID());

    // Create a char array with a fixed size
    char nameBuffer[MAX_NAME_LENGTH];
    strncpy_s(nameBuffer, sizeof(nameBuffer), name.c_str(), _TRUNCATE);
    nameBuffer[sizeof(nameBuffer) - 1] = 0; // Ensure null-termination

    if (ImGui::InputText(inputId.c_str(), nameBuffer, sizeof(nameBuffer), ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll)) {
        selectedNode->SetName(std::string(nameBuffer));
    }

    // Render common shape properties
    RenderCommonShapeProperties(shape);

    // Render specific shape properties
    if (auto* shape2D = dynamic_cast<Shape2D*>(shape)) {
        RenderShape2DDetails(shape2D);
    } else if (auto* shape3D = dynamic_cast<Shape3D*>(shape)) {
        RenderShape3DDetails(shape3D);
    }
}

void Inspector::RenderCommonShapeProperties(Shape* shape) {
    glm::vec3 position = shape->GetPosition();
    glm::vec3 rotation = shape->GetRotation();
    glm::vec3 size = shape->GetSize();
    glm::vec4 color = shape->GetColor();

    if (ImGui::DragFloat3("Position (x, y, z)", glm::value_ptr(position))) {
        shape->SetPosition(position);
    }
    if (ImGui::DragFloat3("Rotation (x, y, z)", glm::value_ptr(rotation))) {
        shape->SetRotation(rotation);
    }
    if (ImGui::DragFloat3("Size (w, h, d)", glm::value_ptr(size))) {
        shape->SetSize(size);
    }
    if (ImGui::ColorEdit4("Color", glm::value_ptr(color))) {
        shape->SetColor(color);
    }
}

void Inspector::RenderShape2DDetails(Shape2D* shape2D) {
    // Texture Panel for 2D shapes
    if (shape2D->GetSpecificType() != Shape2D::Type::Point && shape2D->GetSpecificType() != Shape2D::Type::Line) {
        if (ImGui::TreeNode("Texture Panel")) {
            texturePanel.Draw(); // Assuming texturePanel is accessible within this scope
            ImGui::TreePop();
        }
    }

    ImGui::Separator(); // Separator for visual distinction
    // Collision Panel
    if (ImGui::TreeNode("Collision")) {
        collisionPanel.DisplaySettings(std::static_pointer_cast<Shape2D>(shape2D->shared_from_this())); // Correct usage assuming Shape2D inherits from std::enable_shared_from_this
        ImGui::TreePop();
    }

    ImGui::Separator(); // Separator for visual distinction
    // RigidBody Panel
    if (ImGui::TreeNode("RigidBody")) {
        RigidBodyPanel rigidBodyPanel(shape2D->GetRigidBody()); // Pass the RigidBody to the constructor
        rigidBodyPanel.Display(); // Call Display without passing the RigidBody
        ImGui::TreePop();
    }
}

void Inspector::RenderShape3DDetails(Shape3D* shape3D) {
    glm::vec3 ambient = shape3D->GetAmbient();
    glm::vec3 diffuse = shape3D->GetDiffuse();
    glm::vec3 specular = shape3D->GetSpecular();
    float shininess = shape3D->GetShininess();

    if (ImGui::ColorEdit3("Ambient Color", glm::value_ptr(ambient))) {
        shape3D->SetAmbient(ambient);
    }
    if (ImGui::ColorEdit3("Diffuse Color", glm::value_ptr(diffuse))) {
        shape3D->SetDiffuse(diffuse);
    }
    if (ImGui::ColorEdit3("Specular Color", glm::value_ptr(specular))) {
        shape3D->SetSpecular(specular);
    }
    if (ImGui::DragFloat("Shininess", &shininess, 0.1f, 0.0f, 128.0f)) {
        shape3D->SetShininess(shininess);
    }
}

void Inspector::Render() {
    auto selectedNodes = scenePanel.GetSelectedNodes();
    if (selectedNodes.empty() && openTabs.empty()) {
        lastSelectedNode = nullptr;
        return;
    }

    // Add the ImGuiWindowFlags_AlwaysAutoResize flag
    if (!ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::End();
        return;
    }

    // Update the open tabs based on current selection
    for (auto* node : selectedNodes) {
        if (!node->IsOpenInTab()) {
            // Mark the node as open in a tab if it's newly selected
            openTabs[node->GetID()] = true;
            node->SetOpenInTab(true);
        }
    }

    // Delegate to RenderTabs to draw UI for all open tabs
    RenderTabs();

    ImGui::End();
}

void Inspector::RenderNodeProperties(SceneNode* node) {
    // Node name editing
    char nameBuffer[128];
    strncpy_s(nameBuffer, node->GetName().c_str(), sizeof(nameBuffer));
    nameBuffer[sizeof(nameBuffer) - 1] = '\0'; // Ensure null termination

    if (ImGui::InputText("Name", nameBuffer, sizeof(nameBuffer))) {
        node->SetName(nameBuffer);
    }
}

void Inspector::RenderTabs() {
    if (ImGui::BeginTabBar("ShapeTabs")) {
        RenderExistingTabs();
        AddNewTabs();
        ImGui::EndTabBar();
    }
}

void Inspector::RenderExistingTabs() {
    std::vector<int> toClose;
    for (const auto& entry : openTabs) {
        SceneNode* node = sceneManager->FindNodeById(entry.first);
        if (node && entry.second) {
            RenderTab(node, toClose);
        }
    }
    CloseTabs(toClose);
}

void Inspector::RenderTab(SceneNode* node, std::vector<int>& toClose) {
    std::string tabTitle = node->GetName();
    bool isOpen = true;

    if (ImGui::BeginTabItem(tabTitle.c_str(), &isOpen)) {
        RenderShapeDetails(node->GetShape().get(), node);
        ImGui::EndTabItem();
    }

    if (!isOpen) {
        toClose.push_back(node->GetID());
        node->SetOpenInTab(false);
    }
}

void Inspector::CloseTabs(std::vector<int>& toClose) {
    for (int id : toClose) {
        openTabs.erase(id);
    }
}

void Inspector::AddNewTabs() {
    // Get the currently selected nodes from the ScenePanel
    std::vector<SceneNode*> selectedNodes = scenePanel.GetSelectedNodes();
    for (SceneNode* selectedNode : selectedNodes) {
        // Check if this node is already open in a tab
        if (!selectedNode->IsOpenInTab()) {
            // Node is not open in a tab, so add it
            openTabs[selectedNode->GetID()] = true;
            selectedNode->SetOpenInTab(true);
        }
    }
}

void Inspector::OnTextureLoaded(int textureId) { // Wh
    std::vector<SceneNode*> selectedNodes = scenePanel.GetSelectedNodes();
    if (!selectedNodes.empty()) {
        SceneNode* selectedNode = selectedNodes[0];
        Shape* shape = selectedNode->GetShape().get();
        shape->SetTextureId(textureId);  // Use SetTextureId instead of SetTexture
    }
}

} // namespace RavenEngine