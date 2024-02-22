// sceneserializer.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes
#include <string>
#include <memory>
// Third party includes

// Raven includes
#include "SceneNode.h"

namespace RavenEngine {
class SceneSerializer {
public:
    std::string Serialize(const SceneNode& node);
    std::unique_ptr<SceneNode> Deserialize(const std::string& data);
};
} // namespace RavenEngine