// ShapeCreate.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
#include <map>
#include <memory>

// Third party includes

// Local project includes
#include "../../Assets/Shaders/ShaderManager.h"
#include "ShapeCreate.h"
#include "Shape2D/Point.h"
#include "Shape2D/Line.h"
#include "Shape2D/Plane.h"
#include "Shape2D/Triangle.h"
#include "Shape2D/TriQuad.h"

namespace RavenEngine {

std::shared_ptr<Shape2D> ShapeCreate::CreateShape(Shape2D::Type shapeType) {
    // Create a map to keep track of the number of shapes of each type
    static std::map<Shape2D::Type, int> shapeCounts;
    shapeCounts[shapeType]++;
    int newID = shapeCounts[shapeType];
    std::string shapeTypeName = Shape2D::GetTypeName(shapeType);

    std::shared_ptr<Shape2D> shape;
    switch (shapeType) {
        case Shape2D::Type::Point:
            shape = std::make_shared<Point>(); 
            break;
        case Shape2D::Type::Line:
            shape = std::make_shared<Line>(); 
            break;
        case Shape2D::Type::Triangle:
            shape = std::make_shared<Triangle>(); 
            break;
        case Shape2D::Type::Plane:
            shape = std::make_shared<Plane>(); 
            break;
        case Shape2D::Type::TriQuad:
            shape = std::make_shared<TriQuad>();
            break;
        default:
            throw std::invalid_argument("Invalid shape type");
    }

    // Initialize (Create) the shape
    shape->Create(); // Assuming all Shape2D derived classes have a Create method

    // Load default shader (temporarily here, consider moving this later)
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    if (!shaderManager.IsShaderLoaded("defaultShader")) { // Check if the shader is already loaded
        if (!shaderManager.LoadShader("defaultShader", "D:/RavenEngineProject/RavenEngine/Assets/Shaders/VertexShader.glsl", "D:/RavenEngineProject/RavenEngine/Assets/Shaders/FragmentShader.glsl")) {
            throw std::runtime_error("ShapeCreate::CreateShape FAILED to load default shader");
        }
    }
    shape->SetShaderName("defaultShader");

    

    std::cout << "ShapeCreate::CreateShape created: " << shapeTypeName << std::endl;
    return shape;
}

} // namespace RavenEngine