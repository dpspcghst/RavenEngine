// Inspector.cpp
#include <imgui.h>
#include "Inspector.h"
#include "../Scene/SceneManager.h"
#include "../Scene/ScenePanel.h"
#include "../Scene/SceneNode.h"
#include "../Renderer/Shapes/Shape2D/Shape2D.h"

namespace RavenEngine {

Inspector::Inspector(ScenePanel& scenePanel) // Change SceneManager to ScenePanel
    : scenePanel(scenePanel) { // Change sceneManager to scenePanel
}

void Inspector::Render() {
    std::vector<SceneNode*> selectedNodes = scenePanel.GetSelectedNodes();
    bool isOpen = !selectedNodes.empty();

    if (isOpen) {
        SceneNode* selectedNode = selectedNodes[0];
        auto shape2D = dynamic_cast<Shape2D*>(selectedNode->GetShape().get());

        if (ImGui::Begin("Inspector", &isOpen, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse)) {
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

                // Position
                if (ImGui::DragFloat3("Position", &position.x)) {
                    shape2D->SetPosition(position);
                }

                // Rotation
                if (ImGui::DragFloat3("Rotation", &rotation.x)) {
                    shape2D->SetRotation(rotation);
                }

                // Size
                if (ImGui::DragFloat3("Size", &size.x)) {
                    shape2D->SetSize(size);
                }
            }

            ImGui::End();
        }
    }
}

} // namespace RavenEngine
