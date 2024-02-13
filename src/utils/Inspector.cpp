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

namespace RavenEngine {

Inspector::Inspector(ScenePanel& scenePanel, TextureManager& textureManager)
    : scenePanel(scenePanel), 
      texturePanel(textureManager, [this](int textureId) { this->OnTextureLoaded(textureId); }) {
}

void Inspector::OnTextureLoaded(int textureId) {
    // Handle the event when a new texture is loaded.
    // For example, you can update the texture of the selected shape here.
    std::vector<SceneNode*> selectedNodes = scenePanel.GetSelectedNodes();
    if (!selectedNodes.empty()) {
        SceneNode* selectedNode = selectedNodes[0];
        Shape* shape = selectedNode->GetShape().get();
        shape->SetTextureId(textureId);  // Use SetTextureId instead of SetTexture
    }
}

void Inspector::Render() {
    std::vector<SceneNode*> selectedNodes = scenePanel.GetSelectedNodes();
    if (selectedNodes.empty()) {
        return;
    }

    SceneNode* selectedNode = selectedNodes[0];
    Shape* shape = selectedNode->GetShape().get();

    if (!ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) { // Begin the inspector window
        ImGui::End();
        return;
    }

    char name[128];
    strncpy_s(name, sizeof(name), selectedNode->GetName().c_str(), _TRUNCATE);
    if (ImGui::InputText("Name", name, sizeof(name))) { // Input text for the name
        selectedNode->SetName(name);
    }

    // Common properties for all shapes
    glm::vec3 position = shape->GetPosition();
    glm::vec3 rotation = shape->GetRotation();
    glm::vec3 size = shape->GetSize();
    glm::vec4 color = shape->GetColor();

    if (ImGui::DragFloat3("Position (x, y, z)", &position.x)) {
        shape->SetPosition(position);
    }

    if (ImGui::DragFloat3("Rotation (x, y, z)", &rotation.x)) {
        shape->SetRotation(rotation);
    }

    if (ImGui::DragFloat3("Size (w, h, d)", &size.x)) {
        shape->SetSize(size);
    }

    if (ImGui::ColorEdit4("Color", glm::value_ptr(color))) {
        shape->SetColor(color);
    }

    // Shape-specific attributes
    if (auto* shape3D = dynamic_cast<Shape3D*>(shape)) {
        // Material properties for 3D shapes
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
    // Further shape-specific handling can be added here with else if or if blocks
    ImGui::Separator();
    
    texturePanel.Draw(); // Draw the texture panel

    ImGui::End();
}

} // namespace RavenEngine
