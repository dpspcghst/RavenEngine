// sceneserializer.cpp
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes

// Raven includes
#include "SceneSerializer.h"

namespace RavenEngine {
std::string SceneSerializer::Serialize(const SceneNode& node) {
    return "Name: " + node.GetName() + ", ID: " + std::to_string(node.GetID());
}

std::unique_ptr<SceneNode> SceneSerializer::Deserialize(const std::string& data) {
    auto node = std::make_unique<SceneNode>();
    node->SetName("Default Name");
    node->SetID(0);
    return node;
}

} // namespace RavenEngine