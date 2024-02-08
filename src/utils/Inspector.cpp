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

namespace RavenEngine {

Inspector::Inspector(ScenePanel& scenePanel)
    : scenePanel(scenePanel) {
}

void Inspector::Render() {
    std::vector<SceneNode*> selectedNodes = scenePanel.GetSelectedNodes();
    if (selectedNodes.empty()) {
        return;
    }

    SceneNode* selectedNode = selectedNodes[0];
    Shape* shape = selectedNode->GetShape().get();

    if (!ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
        ImGui::End();
        return;
    }

    char name[128];
    strncpy_s(name, sizeof(name), selectedNode->GetName().c_str(), _TRUNCATE);
    if (ImGui::InputText("Name", name, sizeof(name))) {
        selectedNode->SetName(name);
    }

    // Since position, rotation, size, and color are common to all shapes, handle them generically
    glm::vec3 position = shape->GetPosition();
    glm::vec3 rotation = shape->GetRotation();
    glm::vec3 size = shape->GetSize(); // Ensure that Shape3D also uses GetSize and SetSize. If it uses scale, replace these with GetScale and SetScale.
    glm::vec4 color = shape->GetColor();

    // Position
    if (ImGui::DragFloat3("Position (x, y, z)", &position.x)) {
        shape->SetPosition(position);
    }

    // Rotation
    if (ImGui::DragFloat3("Rotation (x, y, z)", &rotation.x)) {
        shape->SetRotation(rotation);
    }

    // Size/Scale
    if (ImGui::DragFloat3("Size (w, h, d)", &size.x)) {
        shape->SetSize(size); // Replace with SetScale if Shape3D uses scale
        //output size to console
        std::cout << "INSPECTOR::RENDER Size: " << glm::to_string(size) << std::endl;
    }

    // Color
    if (ImGui::ColorEdit4("Color", glm::value_ptr(color))) {
        shape->SetColor(color);
    }

    // Shape-specific attributes
    // For Shape2D or Shape3D specific attributes, you can handle them here using dynamic_cast or GetType to identify the shape type

    ImGui::End();
}


} // namespace RavenEngine
