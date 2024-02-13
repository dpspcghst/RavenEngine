// ShapeCreate2D.cpp

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
#include "../../Materials/MaterialProperties.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Texture/TextureManager.h"
#include "ShapeCreate2D.h"
#include "Point.h"
#include "Line.h"
#include "Rect.h"
#include "Triangle.h"
#include "TriQuad.h"
#include "Circle.h"

namespace RavenEngine {
std::shared_ptr<Shape2D> ShapeCreate2D::CreateShape2D(Shape2D::Type shapeType) {
    static int uboBindingPoint = 0;  // creating a unique binding point for each shape
    static int uniqueID = 1;  // creating a unique ID for each shape
    int defaultTextureId = 0;
    std::string shapeTypeName = Shape2D::GetTypeName(shapeType);
    std::string entityName = shapeTypeName + "_" + std::to_string(uniqueID);

    std::shared_ptr<Shape2D> shape2D;
    switch (shapeType) {
        case Shape2D::Type::Point:
            shape2D = std::make_shared<Point>(); 
            break;
        case Shape2D::Type::Line:
            shape2D = std::make_shared<Line>(); 
            break;
        case Shape2D::Type::Triangle:
            shape2D = std::make_shared<Triangle>(); 
            break;
        case Shape2D::Type::Rect:
            shape2D = std::make_shared<Rect>(); 
            break;
        case Shape2D::Type::TriQuad:
            shape2D = std::make_shared<TriQuad>();
            break;
        case Shape2D::Type::Circle:
            shape2D = std::make_shared<Circle>();
            break;
        default:
            throw std::invalid_argument("Invalid shape type");
    }
    
    shape2D->Create();
    std::cout << "SHAPECREATE::2D Created " << Shape2D::GetTypeName(shapeType) << " shape" << std::endl;

    // Load default shader and set shader name for the shape
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    const std::string defaultShaderName = "defaultShader";
    if (!shaderManager.IsShaderLoaded(defaultShaderName)) {
        shaderManager.LoadShader(defaultShaderName, "../src/Renderer/Shaders/VertexShader.glsl", "../src/Renderer/Shaders/FragmentShader.glsl");
    }
    shape2D->SetShaderName(defaultShaderName);

    // Debug print
    std::cout << "SHAPECREATE2D::CREATESHAPE2D Shader loaded and set for shape: " << shape2D->GetID() << std::endl;
    // Create a UBO for the shape's material properties
    std::string uboName = "MaterialProperties_" + std::to_string(uniqueID);
    size_t uboSize = sizeof(MaterialProperties);
    // Create a UBO for the shape
    UniformBufferManager& uniformBufferManager = UniformBufferManager::GetInstance();
    uniformBufferManager.CreateUniformBuffer(uboName, uboSize, uboBindingPoint);
    // Log the UBO's name, size, and binding point
    shape2D->SetMaterialUBOName(uboName);
    // Initialize color for the shape and update its UBO
    glm::vec4 initialColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Default color: white
    shape2D->SetColor(initialColor);  // Set the shape's color (this will internally update the UBO)

    // Get the shader program
    std::shared_ptr<RavenEngine::ShaderProgram> shaderProgramPtr = shaderManager.GetShader("defaultShader");
    if (!shaderProgramPtr) {
        std::cerr << "SHAPECREATE::2D Failed to get valid shader program for: " << defaultShaderName << std::endl;
        return nullptr;
    }

    // Get the GLuint representing the shader program
    GLuint shaderProgram = shaderProgramPtr->GetID();
    std::cout << "SHAPECREATE::2D Shader program ID: " << shaderProgram << std::endl;
    if (!shaderProgram || !glIsProgram(shaderProgram)) { // If the shader program is invalid
        std::cerr << "SHAPECREATE::2D Failed to get valid shader program for: " << defaultShaderName << std::endl;
        return nullptr;
    }
    glUseProgram(shaderProgram);

    // Bind UBO to shader's uniform block
    GLuint blockIndex = glGetUniformBlockIndex(shaderProgram, "MaterialProperties");
    if (blockIndex == GL_INVALID_INDEX) {
        std::cerr << "SHAPECREATE::2D Uniform block 'MaterialProperties' not found in shader program: " << shaderProgram << std::endl;
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
    ++uniqueID;

    return shape2D;
}

} // namespace RavenEngine