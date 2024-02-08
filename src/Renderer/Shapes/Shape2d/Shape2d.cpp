// Shape2D.cpp

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
#include "Shape2D.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Materials/MaterialProperties.h"

namespace RavenEngine {

const std::vector<Shape2D::Type> Shape2D::AllTypes = { Shape2D::Type::Point, Shape2D::Type::Line, Shape2D::Type::Triangle, Shape2D::Type::Rect, Shape2D::Type::TriQuad, Shape2D::Type::Circle };

Shape2D::Shape2D() 
    : Shape() {
    type = Type::Point; // Default type can be set here
    glGenBuffers(1, &ubo); // Generate UBO here
    ID = nextID++;
    UpdateTransformMatrix();
}

Shape2D::Shape2D(const glm::vec3& pos, Type type) 
    : Shape() {
    this->position = pos; // Position is now in the base class
    this->type = type;
    glGenBuffers(1, &ubo); // Generate UBO here
    ID = nextID++;
    UpdateTransformMatrix();
}

Shape2D::Shape2D(const std::string& shaderName) {
    glGenBuffers(1, &ubo); // Generate UBO here
    ID = nextID++;
    UpdateTransformMatrix();
}

Shape2D::~Shape2D() {
    glDeleteBuffers(1, &ubo);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Shape2D::SetShaderName(const std::string& shaderName) {
    Shape::SetShaderName(shaderName);  // Call the base class method

    std::cout << "SHAPE2D::SETSHADERNAME Shader name set to: " << this->shaderName 
              << ", Shader program ID set to: " << this->shaderProgram << std::endl;

    if (glIsProgram(this->shaderProgram) == GL_FALSE) {
        std::cerr << "SHAPE2D::SETSHADERNAME Invalid shader program ID: " << this->shaderProgram << std::endl;
    } else {
        std::cout << "SHAPE2D::SETSHADERNAME Valid shader program ID: " << this->shaderProgram << std::endl;
    }
}

void Shape2D::SetMaterialUBOName(const std::string& name) {
    Shape::SetMaterialUBOName(name);  // Call the base class method

    std::cout << "SHAPE2D::SETMATERIALUBONAME Material UBO name set to: " << materialUBOName << std::endl;
}

std::string Shape2D::GetMaterialUBOName() const {
    std::cout << "SHAPE2D::GETMATERIALUBONAME Retrieved material UBO name: " << materialUBOName << std::endl;

    return Shape::GetMaterialUBOName();  // Call the base class method
}

Shape2D::Type Shape2D::GetSpecificType() const {
    return type;
}

// Implement GetType from the base class to return ShapeType
Shape::ShapeType Shape2D::GetType() const {
    return Shape::ShapeType::Shape2D;
}

std::string Shape2D::GetTypeName(Type type) {
    switch (type) {
        case Type::Point: return "Point";
        case Type::Line: return "Line";
        case Type::Triangle: return "Triangle";
        case Type::Rect: return "Rect";
        case Type::TriQuad: return "TriQuad";
        case Type::Circle: return "Circle";
        default: return "Unknown";
    }
}

void Shape2D::UpdateTransformMatrix() {
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, position);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transformMatrix = glm::scale(transformMatrix, size);
    // debug
    std::cout << "Shape2D size: " << glm::to_string(size) << std::endl;
    std::cout << "SHAPE2D::UPDATETRANSFORMMATRIX Transform matrix: " << glm::to_string(transformMatrix) << std::endl;
}

} // namespace RavenEngine