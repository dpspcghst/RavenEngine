// ShapeCreate3D.h

// Standard library includes
#include <memory>

// Third party includes

// Raven includes
#include "../../Shaders/ShaderManager.h"
#include "../../../Scene/SceneNode.h"
#include "../../Materials/MaterialManager.h"
#include "Shape3D.h"

namespace RavenEngine {

class ShapeCreate3D {
public:
    std::shared_ptr<Shape3D> CreateShape3D(Shape3D::Type shapeType);

private:
    MaterialManager materialManager; // Add MaterialManager member
};

} // namespace RavenEngine