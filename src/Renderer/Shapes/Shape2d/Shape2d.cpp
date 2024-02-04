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

int Shape2D::nextID = 0;

Shape2D::Shape2D() 
    : VAO(0), VBO(0), ubo(0), // Initialize ubo here
      size(1.0f, 1.0f, 0.0f), 
      position(0.0f, 0.0f, 0.0f), rotation(0.0f), 
      color(1.0f, 1.0f, 1.0f, 1.0f), 
      transformMatrix(1.0f) {
    glGenBuffers(1, &ubo); // Generate UBO here
    ID = nextID++;
    UpdateTransformMatrix();
}

Shape2D::Shape2D(const glm::vec3& pos, Type type) 
    : VAO(0), VBO(0), ubo(0), // Initialize ubo here
      size(1.0f, 1.0f, 0.0f), 
      position(pos), type(type), rotation(0.0f), 
      color(1.0f, 1.0f, 1.0f, 1.0f), // Default color: white
      transformMatrix(1.0f) {
    glGenBuffers(1, &ubo); // Generate UBO here
    ID = nextID++;
    UpdateTransformMatrix();
}

Shape2D::Shape2D(const std::string& shaderName) 
    : VAO(0), VBO(0), ubo(0), // Initialize ubo here
      size(1.0f, 1.0f, 0.0f), 
      position(0.0f, 0.0f, 0.0f), rotation(0.0f), 
      color(1.0f, 1.0f, 1.0f, 1.0f), // Default color: white
      transformMatrix(1.0f), shaderName(shaderName) {
    glGenBuffers(1, &ubo); // Generate UBO here
    ID = nextID++;
    UpdateTransformMatrix();
}

Shape2D::~Shape2D() {
    glDeleteBuffers(1, &ubo);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

Shape2D::Type Shape2D::GetType() const {
    return type;
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

glm::vec3 Shape2D::GetSize() const {
    return size;
}

void Shape2D::SetSize(const glm::vec3& newSize) {
    size = newSize;
    UpdateTransformMatrix();
}

glm::vec3 Shape2D::GetPosition() const {
    return position;
}

void Shape2D::SetPosition(const glm::vec3& newPosition) {
    position = newPosition;
    UpdateTransformMatrix();
    //std::cout << "SHAPE2D::SETPOSITION Position set to: " << position.x << ", " << position.y << ", " << position.z << std::endl;
}

glm::vec3 Shape2D::GetRotation() const {
    return rotation;
}

void Shape2D::SetRotation(const glm::vec3& newRotation) {
    rotation = newRotation;
    UpdateTransformMatrix();
}

void Shape2D::UpdateTransformMatrix() {
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::translate(transformMatrix, position);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transformMatrix = glm::scale(transformMatrix, size);
    // debug
    //std::cout << "SHAPE2D::UPDATETRANSFORMMATRIX Transform matrix: " << glm::to_string(transformMatrix) << std::endl;
}

void Shape2D::SetShaderName(const std::string& shaderName) {
    this->shaderName = shaderName;
    this->shaderProgram = ShaderManager::GetInstance().GetShader(shaderName);
    std::cout << "SHAPE2D::SETSHADERNAME Shader name set to: " << this->shaderName 
              << ", Shader program ID set to: " << this->shaderProgram << std::endl;

    if (glIsProgram(this->shaderProgram) == GL_FALSE) {
        std::cerr << "SHAPE2D::SETSHADERNAME Invalid shader program ID: " << this->shaderProgram << std::endl;
    } else {
        std::cout << "SHAPE2D::SETSHADERNAME Valid shader program ID: " << this->shaderProgram << std::endl;
    }
}

const std::string& Shape2D::GetShaderName() const {
    return shaderName;
}

void Shape2D::SetID(int id) {
    ID = id;
}

int Shape2D::GetID() const {
    return ID;
}

void Shape2D::SetMaterialUBOName(const std::string& name) {
    materialUBOName = name;
    std::cout << "SHAPE2D::SETMATERIALUBONAME Material UBO name set to: " << materialUBOName << std::endl;
}

std::string Shape2D::GetMaterialUBOName() const {
    std::cout << "SHAPE2D::GETMATERIALUBONAME Retrieved material UBO name: " << materialUBOName << std::endl;
    return materialUBOName;
}

void Shape2D::SetColor(const glm::vec4& newColor) {  
    color = newColor;
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    MaterialProperties props{color};

    std::cout << "SHAPE2D::SETCOLOR Material UBO Name: " << materialUBOName 
              << ", New Color: (" << newColor.r << ", " << newColor.g << ", " << newColor.b << ", " << newColor.a << ")\n";

    shaderManager.UpdateUniformBuffer(materialUBOName, &props, sizeof(props));

    MaterialProperties readBackProps;
    shaderManager.GetUBOData(materialUBOName, &readBackProps, sizeof(readBackProps));
    std::cout << "SHAPE2D::SETCOLOR Read back UBO data: Color: (" << readBackProps.color.r << ", " << readBackProps.color.g << ", " << readBackProps.color.b << ", " << readBackProps.color.a << ")\n";
}


glm::vec4 Shape2D::GetColor() const {
    return color;
}

} // namespace RavenEngine