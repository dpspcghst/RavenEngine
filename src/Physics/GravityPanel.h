// GravityPanel.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

// Third party includes

// Raven includes
#include "GravityManager.h"
#include "../Renderer/Shapes/Shape2D/Shape2D.h"

namespace RavenEngine {
class GravityPanel {
public:
    GravityPanel(Shape2D* shape2D, GravityManager& gravityManager)
        : shape2D(shape2D), gravityManager(gravityManager) {}

    void Display();

    bool IsGravityEnabled() const {
        return isGravityEnabled;
    }


private:
    Shape2D* shape2D;
    GravityManager& gravityManager;
    bool isGravityEnabled = false;
};
} // namespace RavenEngine