// ShapeCreate.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>

// Third party includes
#include <glm/gtx/string_cast.hpp>

// Raven includes
#include "../Materials/MaterialProperties.h"
#include "../Shaders/ShaderManager.h"
#include "../../src/Renderer/UBO/UniformBuffer.h"
#include "ShapeCreate.h"
#include "Shape2D/Point.h"
#include "Shape2D/Line.h"
#include "Shape2D/Rect.h"
#include "Shape2D/Triangle.h"
#include "Shape2D/TriQuad.h"
#include "Shape2D/Circle.h"

namespace RavenEngine {
std::shared_ptr<Shape2D> ShapeCreate::CreateShape(Shape2D::Type shapeType) {
    static int uboBindingPoint = 0;  // creating a unique binding point for each shape
    static int uniqueID = 0;  // creating a unique ID for each shape
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
        case Shape2D::Type::Rect:
            shape = std::make_shared<Rect>(); 
            break;
        case Shape2D::Type::TriQuad:
            shape = std::make_shared<TriQuad>();
            break;
        case Shape2D::Type::Circle:
            shape = std::make_shared<Circle>();
            break;
        default:
            throw std::invalid_argument("Invalid shape type");
    }
    
    shape->Create(); 
    shape->SetID(++uniqueID); // Increment and assign unique ID
    std::cout << "SHAPECREATE::CREATESHAPE Created shape with uniqueID: " << uniqueID << std::endl;

    // Load default shader and set shader name for the shape
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    const std::string defaultShaderName = "defaultShader";
    if (!shaderManager.IsShaderLoaded(defaultShaderName)) {
        shaderManager.LoadShader(defaultShaderName, "../src/Renderer/Shaders/VertexShader.glsl", "../src/Renderer/Shaders/FragmentShader.glsl");
    }
    shape->SetShaderName(defaultShaderName);

    // Create a unique UBO name using the shape's unique ID
    std::string uboName = "MaterialProperties_" + std::to_string(uniqueID);
    size_t uboSize = sizeof(MaterialProperties);

    // Create UBO for the shape
    shaderManager.CreateUniformBuffer(uboName, uboSize, uboBindingPoint);

    // Log the UBO's name, size, and binding point
    std::cout << "SHAPECREATE::CREATESHAPE Created UBO with name: " << uboName 
              << ", size: " << uboSize 
              << ", binding point: " << uboBindingPoint << std::endl;

    shape->SetMaterialUBOName(uboName);

    // Initialize color for the shape and update its UBO
    glm::vec4 initialColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Default color: white
    shape->SetColor(initialColor);  // Set the shape's color (this will internally update the UBO)

    // Bind UBO to the shader
    GLuint shaderProgram = shaderManager.GetShader(defaultShaderName);
    if (!shaderProgram || !glIsProgram(shaderProgram)) {
        std::cerr << "SHAPECREATE::CREATESHAPE Failed to get valid shader program for: " << defaultShaderName << std::endl;
        return nullptr;
    }
    glUseProgram(shaderProgram);

    // Bind UBO to shader's uniform block
    GLuint blockIndex = glGetUniformBlockIndex(shaderProgram, "MaterialProperties");
    if (blockIndex == GL_INVALID_INDEX) {
        std::cerr << "Uniform block 'MaterialProperties' not found in shader program: " << shaderProgram << std::endl;
        return nullptr;
    }
    glUniformBlockBinding(shaderProgram, blockIndex, uboBindingPoint);

    // Unbind the UBO and the shader program
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glUseProgram(0);

    // Unbind the VAO
    glBindVertexArray(0);

    // Increment the unique binding point for the next shape
    ++uboBindingPoint;

    return shape;
}

} // namespace RavenEngine