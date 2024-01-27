// ShapeCreate.h

// #include section
// #####################

// Standard library includes
#include <memory>

// Third party includes

// Raven includes
#include "../../../Assets/Shaders/ShaderManager.h" // Include ShaderManager
#include "../../Scene/SceneNode.h" // Include SceneNode

namespace RavenEngine {

class ShapeCreate {
public:
    std::shared_ptr<Shape2D> CreateShape(Shape2D::Type shapeType);
};

} // namespace RavenEngine