// scene.h
// #####################
#ifndef SCENE_H
#define SCENE_H
// #include section
// #####################
// Standard library includes
#include <memory>
// Third-party includes

// Raven includes
#include "../Renderer/Camera/Camera.h"
#include "SceneNode.h"
#include "SceneGraphRenderer.h"
// Forward declarations

namespace RavenEngine {

class Scene {
public:
    Scene(); // Constructor
    ~Scene(); // Destructor

    void Initialize(); // Initialize the scene
    void Update(float deltaTime); // Update the scene
    void Render(); // Render the scene
    void Destroy(); // Clean up the scene

private:
    std::unique_ptr<SceneGraphRenderer> sceneGraphRenderer;
    std::shared_ptr<Camera> camera; // The main camera for the scene
    SceneNode rootNode; // The root node of the scene graph
};

} // namespace RavenEngine

// Include necessary headers here

#endif // SCENE_H