// scenepanel.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
#include <memory>
#include <utility>

// Third-party libraries
#include <imgui.h>

// Raven includes
#include "ScenePanel.h"
#include "../Renderer/Shapes/Shape2D/ShapeCreate2D.h"
#include "../Renderer/Shapes/Shape2D//Point.h"
#include "../Renderer/Shapes/Shape2D/Line.h"
#include "../Renderer/Shapes/Shape2D/Rect.h"
#include "../Renderer/Shapes/Shape2D/Triangle.h"
#include "../Renderer/Shapes/Shape2D/TriQuad.h"

#include "../Renderer/Shapes/Shape3D/ShapeCreate3D.h"
#include "../Renderer/Shapes/Shape3D/Cube.h"

namespace RavenEngine {

ScenePanel::ScenePanel(ShaderManager& shaderManagerInstance)
    : shaderManagerInstance(shaderManagerInstance), width(0), height(0) {
    // init code
    //std::cout << "ScenePanel constructor completed successfully" << std::endl;
}

void ScenePanel::SetSize(int width, int height) {
    this->width = width;
    this->height = height;
}

void ScenePanel::SetSceneManager(SceneManager* newSceneManager) {                // Set the scene manager
    sceneManager = newSceneManager;
    selectedNodes.clear();
    nodeToRename = nullptr;
    renameRequested = false;
    //std::cout << "Scene manager set" << std::endl;
}

void ScenePanel::OnImGuiRender() {                                               // Render the ScenePanel

    //std::cout << "ScenePanel::OnImGuiRender()" << std::endl;
    ImGui::Begin("Scene");                                                      // Begin the ImGui window (ScenePanel Name)

    HandleNodeDeletion();                                                       // Handle node deletion
    HandleNodeCreation();
    DrawSceneNodes();

    
    ImGui::End();
}

void ScenePanel::DrawSceneNodes() {                                             
    if (sceneManager) {
        const auto& nodes = sceneManager->GetAllNodes();  // Call GetAllNodes instead of GetNodes
        //std::cout << "Number of nodes: " << nodes.size() << std::endl;
        for (const auto& node : nodes) {  
            DrawNodeTree(node);                                            
        }
    }
}

void ScenePanel::DrawNodeTree(SceneNode* node) {                                 // Draw node tree

    if (!node) {                                                                 // Check if the node is null (invalid)
        std::cerr << "Attempted to draw a null SceneNode." << std::endl;        // If the node is null, print an error message
        return;                                                                 // Return early
    }

    //std::cout << "Processing node: " << node->GetName() << std::endl;           // Print the node name to the console

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth; // Set the node flags

    if (node->GetChildren().empty()) {                                           // Check if the node is a leaf node("w/o children")
        flags |= ImGuiTreeNodeFlags_Leaf;                                      // If the node is a leaf node, add the leaf flag
    }

    // check if selected
    if (std::find(selectedNodes.begin(), selectedNodes.end(), node) != selectedNodes.end()) { 
        flags |= ImGuiTreeNodeFlags_Selected;                                   // If the node is selected, add the selected flag
    }

    ImGui::PushID(node->GetID());                                               // Push the node ID to the ImGui stack

    bool isRenaming = (nodeToRename == node && renameRequested);                // Check if the node is being renamed
    if (isRenaming) {                                                           // If the node is being renamed, draw an input text box
        static char buffer[256] = "";
        if (buffer[0] == '\0') { // Initialize buffer if empty
            strncpy_s(buffer, sizeof(buffer), node->GetName().c_str(), _TRUNCATE);   
                 }
        ImGui::InputText("##edit", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue);
        if (ImGui::IsItemDeactivated()) {
            node->SetName(std::string(buffer));
            buffer[0] = '\0'; // Reset buffer
            nodeToRename = nullptr;
            renameRequested = false;
        }
    } else {                                                                    // If the node is not being renamed, draw the node name
        bool treeNodeOpen = ImGui::TreeNodeEx(node->GetName().c_str(), flags);

        HandleNodeInteraction(node);

        if (treeNodeOpen) {
            for (auto& child : node->GetChildren()) {
                DrawNodeTree(child.get());
            }
            ImGui::TreePop();
        }
    }

    ImGui::PopID();
}

const std::vector<SceneNode*>& ScenePanel::GetSelectedNodes() const {
    return selectedNodes;
}

void ScenePanel::HandleNodeDeletion() {                                         
    //std::cout << "Number of selected nodes: " << selectedNodes.size() << std::endl;  // Add this line
    //std::cout << "Delete key pressed: " << ImGui::IsKeyPressed(ImGuiKey_Delete) << std::endl;  // Add this line
    if (!selectedNodes.empty() && ImGui::IsKeyPressed(ImGuiKey_Delete)) {
        std::cout << "Deleting nodes..." << std::endl;
        for (auto& selectedNode : selectedNodes) {
            sceneManager->RemoveNode(selectedNode);
        }
        selectedNodes.clear();
    }
}

void ScenePanel::HandleNodeInteraction(SceneNode* node) {                       // Handle node interaction
    bool ctrlPressed = ImGui::GetIO().KeyCtrl; // if (ctrlPressed) { ... }
    bool shiftPressed = ImGui::GetIO().KeyShift; // if (shiftPressed) { ... }

                                                                                // todo: add a ctrl+click+arrow to add to selection

    if (ImGui::IsItemClicked()) {                                               // Selection Style (click, ctrl+click, shift+click)
        // Multi-selection with Ctrl key
        if (ctrlPressed) {                                                      // this is like a select one by one
            auto it = std::find(selectedNodes.begin(), selectedNodes.end(), node);
            if (it == selectedNodes.end()) {
                selectedNodes.push_back(node); // Add to selection if not already selected
            } else {
                selectedNodes.erase(it); // Remove from selection if already selected
            }
        } else if (shiftPressed) {                                              // this is like a select all between node "A" and node "B"
            // Range selection with Shift key
            std::vector<SceneNode*> allNodes = sceneManager->GetAllNodes();
            if (selectedNodes.empty()) {
                selectedNodes.push_back(node); // If no nodes are selected, select the current node
            } else {
                // Find the first selected node and the current node in the allNodes list
                auto firstSelectedNodeIt = std::find(allNodes.begin(), allNodes.end(), selectedNodes.front());
                auto currentNodeIt = std::find(allNodes.begin(), allNodes.end(), node);

                // Select all nodes between the first selected node and the current node
                selectedNodes.clear();
                for (auto it = std::min(firstSelectedNodeIt, currentNodeIt); it != std::max(firstSelectedNodeIt, currentNodeIt) + 1; ++it) {
                    selectedNodes.push_back(*it);
                }
            }
        } else {                                                                // default selection style
            // Single selection
            selectedNodes.clear();
            selectedNodes.push_back(node);
        }
    }

    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {             // Double click to rename
        nodeToRename = node;
        renameRequested = true;
    }

    if (ImGui::BeginPopupContextItem()) {                                       // Right click node context menu
        if (ImGui::MenuItem("Rename")) {      // Rename node option
            nodeToRename = node;
            renameRequested = true;
        }
        if (ImGui::MenuItem("Delete")) {      // Delete node/s option (ye olde node removal)
            // Check if the node is in the selectedNodes list
            auto it = std::find(selectedNodes.begin(), selectedNodes.end(), node);
            if (it != selectedNodes.end()) {
                // Node is selected, delete all selected nodes
                for (auto& selectedNode : selectedNodes) {
                    sceneManager->RemoveNode(selectedNode);
                }
                selectedNodes.clear();
            } else {
                // Node is not selected, delete only this node
                sceneManager->RemoveNode(node);
            }
        }
        ImGui::EndPopup(); // End the popup
    }
}

void ScenePanel::HandleNodeCreation() {                                     
    if (ImGui::Button("+Shape")) {
        ImGui::OpenPopup("CreateShapePopup");
    }
    if (ImGui::BeginPopup("CreateShapePopup")) { 
        Handle2DShapeCreationMenu(); // handle 2D shape creation
        Handle3DShapeCreationMenu(); // handle 3D shape creation
        ImGui::EndPopup(); // End the popup
    }
}

void ScenePanel::CreateShape(int shapeType, bool is3D) {
    std::shared_ptr<Shape> newShape;
    std::string shapeTypeName;

    if (is3D) {
        ShapeCreate3D shapeCreate3D;
        // Use the existing CreateShape3D method from ShapeCreate3D
        newShape = shapeCreate3D.CreateShape3D(static_cast<Shape3D::Type>(shapeType));
        shapeTypeName = Shape3D::GetTypeName(static_cast<Shape3D::Type>(shapeType));
    } else {
        ShapeCreate2D shapeCreate2D;
        newShape = shapeCreate2D.CreateShape2D(static_cast<Shape2D::Type>(shapeType));
        shapeTypeName = Shape2D::GetTypeName(static_cast<Shape2D::Type>(shapeType));
    }

    if (newShape) {
        auto newNode = std::make_unique<SceneNode>();
        newNode->SetName(shapeTypeName);
        newNode->AttachShape(newShape);
        sceneManager->AddNode(std::move(newNode));
    } else {
        std::cerr << "Failed to create shape." << std::endl;
    }
}


void ScenePanel::Handle2DShapeCreationMenu() {
    if (ImGui::BeginMenu("2D")) {
        for (auto type : Shape2D::AllTypes) { // Assume Shape2D::AllTypes is a collection of all 2D types
            if (ImGui::MenuItem(Shape2D::GetTypeName(type).c_str())) {
                CreateShape(static_cast<int>(type)); // Create 2D shape
            }
        }
        ImGui::EndMenu();
    }
}

void ScenePanel::Handle3DShapeCreationMenu() {
    if (ImGui::BeginMenu("3D")) {
        for (auto type : Shape3D::AllTypes) { // Assume Shape3D::AllTypes is a collection of all 3D types
            if (ImGui::MenuItem(Shape3D::GetTypeName(type).c_str())) {
                CreateShape(static_cast<int>(type), true); // Create 3D shape
            }
        }
        ImGui::EndMenu();
    }
}

} // namespace RavenEngine