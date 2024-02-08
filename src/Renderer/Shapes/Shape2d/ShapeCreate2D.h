// ShapeCreate2D.h

// #include section
// #####################

// Standard library includes
#include <memory>

// Third party includes

// Raven includes
#include "Shape2D.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Materials/MaterialManager.h"
#include "../../../Scene/SceneNode.h"

namespace RavenEngine {

class ShapeCreate2D {
public:
    std::shared_ptr<Shape2D> CreateShape2D(Shape2D::Type shapeType);

private:
    MaterialManager materialManager; // Add MaterialManager member
};

} // namespace RavenEngine