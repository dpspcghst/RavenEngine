// scenegraphrenderer.h
// #####################
#ifndef SCENE_GRAPH_RENDERER_H
#define SCENE_GRAPH_RENDERER_H
// #include section
// #####################
// Standard library includes
#include <memory>
// Third-party includes

// Raven includes
#include "SceneNode.h"
#include "../Renderer/Camera/Camera.h"
#include "../Renderer/Shapes/ShapeRenderer.h"

namespace RavenEngine {

class SceneGraphRenderer {
public:
    explicit SceneGraphRenderer(std::shared_ptr<Camera> camera);
    void RenderScene(const SceneNode& rootNode);

private:
    std::shared_ptr<Camera> camera;
    std::unique_ptr<ShapeRenderer> shapeRenderer;

    void RenderNode(const SceneNode& node, const glm::mat4& parentTransform);
};

} // namespace RavenEngine

#endif // SCENE_GRAPH_RENDERER_H