// Inspector.h
#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <imgui.h>
#include "../../src/Scene/ScenePanel.h"
#include "../../src/Scene/SceneNode.h"
#include "../../src/Renderer/Shapes/Shape2D/Shape2D.h"
#include "../../src/Renderer/Texture/TexturePanel.h" // Include TexturePanel
#include "../../src/Renderer/Texture/TextureManager.h" // Include TextureManager

namespace RavenEngine {

class Inspector {
public:
    Inspector(ScenePanel& scenePanel, TextureManager& textureManager); // Add TextureManager to constructor

    void Render();

private:
    ScenePanel& scenePanel; // Reference to ScenePanel
    TexturePanel texturePanel; // Add TexturePanel member

    void OnTextureLoaded(int textureId); // Add method to handle the event when a new texture is loaded
};

} // namespace RavenEngine

#endif // INSPECTOR_H