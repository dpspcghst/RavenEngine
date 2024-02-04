// Inspector.cpp

// #include section
// #################
// Standard library includes
#include <iostream>
// Third-party library includes
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
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
    bool isOpen = !selectedNodes.empty();

    if (isOpen) {
        SceneNode* selectedNode = selectedNodes[0];
        auto shape2D = dynamic_cast<Shape2D*>(selectedNode->GetShape().get());

        if (ImGui::Begin("Inspector", &isOpen, ImGuiWindowFlags_AlwaysAutoResize || ImGuiWindowFlags_NoCollapse)) {
            if (shape2D != nullptr) {
                // Name
                char name[128];
                strncpy_s(name, sizeof(name), selectedNode->GetName().c_str(), _TRUNCATE);
                if (ImGui::InputText("Name", name, sizeof(name))) {
                    selectedNode->SetName(name);
                }

                glm::vec3 position = shape2D->GetPosition();
                glm::vec3 rotation = shape2D->GetRotation();
                glm::vec3 size = shape2D->GetSize();
                glm::vec4 color = shape2D->GetColor(); // Get the current color

                // Position
                if (ImGui::DragFloat3("Position (x, y, z)", &position.x)) {
                    shape2D->SetPosition(position);
                }

                // Rotation
                if (ImGui::DragFloat3("Rotation (x, y, z)", &rotation.x)) {
                    shape2D->SetRotation(rotation);
                }

                // Size
                if (ImGui::DragFloat3("Size (w, h, d)", &size.x)) {
                    shape2D->SetSize(size);
                }

                if (ImGui::ColorEdit4("Color", glm::value_ptr(color))) {
                    shape2D->SetColor(color); // Set the new color using the modified color value
                }
            }

            ImGui::End();
        }
        // if (!isOpen) {
        //     std::cout << "'X' button was pressed on the Inspector window.\n";
        // }
    }
}

} // namespace RavenEngine
