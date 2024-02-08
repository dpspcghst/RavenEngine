// Shape3D.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third party includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

// Raven includes
#include "Shape3D.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Materials/MaterialProperties.h"

namespace RavenEngine {

const std::vector<Shape3D::Type> Shape3D::AllTypes = { Shape3D::Type::Cube, Shape3D::Type::Sphere, Shape3D::Type::Cylinder, Shape3D::Type::Cone, Shape3D::Type::Pyramid, Shape3D::Type::Torus, Shape3D::Type::Custom };


Shape3D::Shape3D() 
    : Shape() {
    // Initialization specific to Shape3D, remove members now in the base class
    type = Type::Custom; // Default type can be set here
}

Shape3D::Shape3D(const glm::vec3& pos, Type type) 
    : Shape() {
    // Initialization specific to Shape3D, remove members now in the base class
    this->position = pos; // Position is now in the base class
    this->type = type;
}

Shape3D::Shape3D(const std::string& shaderName) 
    : Shape(shaderName) {
    // Initialization specific to Shape3D, remove members now in the base class
    type = Type::Custom; // Default type can be set here
}

Shape3D::~Shape3D() {
    // Clean up specific to Shape3D, remove members now in the base class
    // The base class destructor handles its own clean up
}

void Shape3D::SetShaderName(const std::string& shaderName) {
    Shape::SetShaderName(shaderName);  // Call the base class method

    std::cout << "SHAPE3D::SETSHADERNAME Shader name set to: " << this->shaderName 
              << ", Shader program ID set to: " << this->shaderProgram << std::endl;

    if (glIsProgram(this->shaderProgram) == GL_FALSE) {
        std::cerr << "SHAPE3D::SETSHADERNAME Invalid shader program ID: " << this->shaderProgram << std::endl;
    } else {
        std::cout << "SHAPE3D::SETSHADERNAME Valid shader program ID: " << this->shaderProgram << std::endl;
    }
}

Shape3D::Type Shape3D::GetSpecificType() const {
    return type;
}

// Implement GetType from the base class to return ShapeType
Shape::ShapeType Shape3D::GetType() const {
    return ShapeType::Shape3D;
}

std::string Shape3D::GetTypeName(Type type) {
    switch (type) {
        case Type::Cube: return "Cube";
        case Type::Sphere: return "Sphere";
        case Type::Cylinder: return "Cylinder";
        case Type::Cone: return "Cone";
        case Type::Pyramid: return "Pyramid";
        case Type::Torus: return "Torus";
        case Type::Custom: return "Custom";
        default: return "Unknown";
    }
}

void Shape3D::UpdateTransformMatrix() {
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, position);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transformMatrix = glm::scale(transformMatrix, size);
}

glm::mat4 Shape3D::GetTransformMatrix() const {
    return transformMatrix;
}

} // namespace RavenEngine
