// ShapeCreate3D.cpp

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
#include "../../Materials/MaterialProperties3D.h"
#include "../../Shaders/ShaderManager.h"
#include "../../../src/Renderer/UBO/UniformBuffer.h"
#include "ShapeCreate3D.h"
#include "Cube.h"

namespace RavenEngine {
std::shared_ptr<Shape3D> ShapeCreate3D::CreateShape3D(Shape3D::Type shapeType) {
    static int uboBindingPoint = 0;  // creating a unique binding point for each shape
    static int uniqueID = 0;  // creating a unique ID for each shape
    std::string shapeTypeName = Shape3D::GetTypeName(shapeType);

    std::shared_ptr<Shape3D> shape3D;
    switch (shapeType) {
        case Shape3D::Type::Cube:
            shape3D = std::make_shared<Cube>(); 
            break;
        // Add more cases as needed for other 3D shapes
        default:
            throw std::invalid_argument("Invalid shape type");
    }
    
    shape3D->Create(); 
    shape3D->SetID(++uniqueID); // Increment and assign unique ID

    // Load default shader and set shader name for the shape
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    const std::string defaultShaderName = "defaultShader3D";
    if (!shaderManager.IsShaderLoaded(defaultShaderName)) {
        shaderManager.LoadShader(defaultShaderName, "../src/Renderer/Shaders/VertexShader3D.glsl", "../src/Renderer/Shaders/FragmentShader3D.glsl");
    }
    shape3D->SetShaderName(defaultShaderName);

    // Create a unique UBO name using the shape's unique ID
    std::string uboName = "MaterialProperties3D_" + std::to_string(uniqueID);
    size_t uboSize = sizeof(MaterialProperties3D);

    UniformBufferManager& uniformBufferManager = UniformBufferManager::GetInstance();
    uniformBufferManager.CreateUniformBuffer(uboName, uboSize, uboBindingPoint);

    shape3D->SetMaterialUBOName(uboName);

    // Initialize color for the shape and update its UBO
    glm::vec4 initialColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Default color: white
    shape3D->SetColor(initialColor);  // Set the shape's color (this will internally update the UBO)

    std::shared_ptr<RavenEngine::ShaderProgram> shaderProgramPtr = shaderManager.GetShader(defaultShaderName);
    if (!shaderProgramPtr || !glIsProgram(shaderProgramPtr->GetID())) {
        std::cerr << "SHAPECREATE::CREATESHAPE3D Failed to get valid shader program for: " << defaultShaderName << std::endl;
        return nullptr;
    }
    GLuint shaderProgram = shaderProgramPtr->GetID();
    glUseProgram(shaderProgram);

    // Bind UBO to shader's uniform block
    GLuint blockIndex = glGetUniformBlockIndex(shaderProgram, "MaterialProperties3D");
    if (blockIndex == GL_INVALID_INDEX) {
        std::cerr << "Uniform block 'MaterialProperties3D' not found in shader program: " << shaderProgram << std::endl;
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

    return shape3D;
}
} // namespace RavenEngine