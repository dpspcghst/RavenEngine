// scene.cpp
// #####################
// #include section
// #####################
// Standard library includes

// Third-party includes

// Raven includes
#include "Scene.h"
#include "../Renderer/Camera/Camera.h"
#include "SceneNode.h"
#include "SceneGraphRenderer.h"

namespace RavenEngine {

Scene::Scene() :
    sceneGraphRenderer(nullptr),
    camera(std::make_shared<Camera>(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 100.0f)), // Adjust these values as needed
    rootNode() {
}

Scene::~Scene() { // Destructor
    Destroy();
}

void Scene::Initialize() { 
    // Here you'd set up your camera, load resources, create scene graph nodes, etc.
    camera->SetupPerspective(45.0f, 16.0f/9.0f, 0.1f, 100.0f); // Example setup
}

void Scene::Update(float deltaTime) { 
    // Update the scene state, such as moving objects, animations, physics, etc.
}

void Scene::Render() { 
    // Create the renderer if it does not exist
    if (!sceneGraphRenderer) {
        sceneGraphRenderer = std::make_unique<SceneGraphRenderer>(camera);
    }
    
    // Use the sceneGraphRenderer to render the scene
    sceneGraphRenderer->RenderScene(rootNode);
}

void Scene::Destroy() { 
    // Here you'd clean up resources used by the scene
}

} // namespace RavenEngine