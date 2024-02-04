// ShapeCreate.h

// #include section
// #####################

// Standard library includes
#include <memory>

// Third party includes

// Raven includes
#include "../Shaders/ShaderManager.h"
#include "../../Scene/SceneNode.h"
#include "../Materials/MaterialManager.h"

namespace RavenEngine {

class ShapeCreate {
public:
    std::shared_ptr<Shape2D> CreateShape(Shape2D::Type shapeType);

private:
    MaterialManager materialManager; // Add MaterialManager member
};

} // namespace RavenEngine