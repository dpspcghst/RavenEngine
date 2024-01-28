// Inspector.h
#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <imgui.h>
#include "../../src/Scene/ScenePanel.h"
#include "../../src/Scene/SceneNode.h"
#include "../../src/Renderer/Shapes/Shape2D/Shape2D.h"

namespace RavenEngine {

class Inspector {
public:
    Inspector(ScenePanel& scenePanel); // Change SceneManager to ScenePanel

    void Render();

private:
    ScenePanel& scenePanel; // Change SceneManager to ScenePanel
};

} // namespace RavenEngine

#endif // INSPECTOR_H