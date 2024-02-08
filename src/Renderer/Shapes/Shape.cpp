#include "Shape.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

namespace RavenEngine {

int Shape::nextID = 0;

void Shape::SetShaderName(const std::string& shaderName) {
    this->shaderName = shaderName;
    auto shaderProgramPtr = ShaderManager::GetInstance().GetShader(shaderName);

    if (shaderProgramPtr) {
        this->shaderProgram = shaderProgramPtr->GetID();
        std::cout << "SHAPE::SETSHADERNAME Shader program ID: " << shaderProgram << " for shape: " << ID << std::endl;
    } else {
        std::cerr << "SHAPE::SETSHADERNAME ShaderProgram object is null." << std::endl;
        this->shaderProgram = -1; // Set to invalid or default shader program ID
    }
}

const std::string& Shape::GetShaderName() const {
    return shaderName;
}

void Shape::SetID(int id) {
    ID = id;
    // Add any additional handling needed when an ID is set.
}

int Shape::GetID() const {
    return ID;
}

void Shape::SetMaterialUBOName(const std::string& name) {
    materialUBOName = name;
    // Add any additional handling needed when a Material UBO name is set.
}

std::string Shape::GetMaterialUBOName() const {
    return materialUBOName;
}

void Shape::SetColor(const glm::vec4& newColor) {
    color = newColor;
    UniformBufferManager& uniformBufferManager = UniformBufferManager::GetInstance();
    MaterialProperties props{color};
    uniformBufferManager.UpdateUniformBuffer(materialUBOName, &props, sizeof(props));

    std::cout << "SHAPE::SETCOLOR Material UBO Name: " << materialUBOName 
              << ", New Color: (" << newColor.r << ", " << newColor.g << ", " << newColor.b << ", " << newColor.a << ")\n";

    MaterialProperties readBackProps;
    uniformBufferManager.GetUBOData(materialUBOName, &readBackProps, sizeof(readBackProps));
    std::cout << "SHAPE::SETCOLOR Read back UBO data: Color: (" << readBackProps.color.r << ", " << readBackProps.color.g << ", " << readBackProps.color.b << ", " << readBackProps.color.a << ")\n";
}

glm::vec4 Shape::GetColor() const {
    return color;
}

void Shape::SetSize(const glm::vec3& newSize) {
    size = newSize;
    // Add any additional handling needed when the size is set.
    // print size to console
    std::cout << "SHAPE::SETSIZE Size: " << glm::to_string(size) << std::endl;
    UpdateTransformMatrix();
}

glm::vec3 Shape::GetSize() const {
    //std::cout << "SHAPE::GETSIZE Size: " << glm::to_string(size) << std::endl;
    return size;
}

void Shape::SetPosition(const glm::vec3& newPosition) {
    position = newPosition;
    // Add any additional handling needed when the position is set.
    // print position to console
    std::cout << "SHAPE::SETPOSITION Position: " << glm::to_string(position) << std::endl;
    UpdateTransformMatrix();
}

glm::vec3 Shape::GetPosition() const {
    return position;
    //std::cout << "SHAPE::GETPOSITION Position: " << glm::to_string(position) << std::endl;
}

void Shape::SetRotation(const glm::vec3& newRotation) {
    rotation = newRotation;
    UpdateTransformMatrix();
}

glm::vec3 Shape::GetRotation() const {
    return rotation;
}

// No implementation for GetTransformMatrix() as it is a pure virtual function.
// Derived classes must provide their own implementation.

} // namespace RavenEngine