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
    static int uniqueID = 1;  // creating a unique ID for each shape
    std::string shapeTypeName = Shape3D::GetTypeName(shapeType);
    std::string entityName = shapeTypeName + "_" + std::to_string(uniqueID);

    std::shared_ptr<Shape3D> shape3D;
    switch (shapeType) {
        case Shape3D::Type::Cube:
            shape3D = std::make_shared<Cube>();
            std::cout << "SHAPECREATE::3D Created " << Shape3D::GetTypeName(shapeType) << " shape" << std::endl; 
            break;
        // Add more cases as needed for other 3D shapes
        default:
            throw std::invalid_argument("Invalid shape type");
    }
    
    shape3D->Create();
    std::cout << "SHAPECREATE::3D Created " << Shape3D::GetTypeName(shapeType) << " shape" << std::endl;

    // Load default shader and set shader name for the shape
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    const std::string defaultShaderName = "defaultShader3D";
    if (!shaderManager.IsShaderLoaded(defaultShaderName)) {
        shaderManager.LoadShader(defaultShaderName, "../src/Renderer/Shaders/VertexShader3D.glsl", "../src/Renderer/Shaders/FragmentShader3D.glsl");
    }
    shape3D->SetShaderName(defaultShaderName);

    // Debug print
    std::cout << "SHAPECREATE2D::CREATESHAPE2D Shader loaded and set for shape: " << shape3D->GetID() << std::endl;

    // Create a UBO for the shape's material properties
    std::string uboName = "MaterialProperties3D_" + std::to_string(uniqueID);
    size_t uboSize = sizeof(MaterialProperties3D);

    UniformBufferManager& uniformBufferManager = UniformBufferManager::GetInstance();
    uniformBufferManager.CreateUniformBuffer(uboName, uboSize, uboBindingPoint);
    // Log the UBO's name, size, and binding point
    std::cout << "SHAPECREATE::3D Created UBO with name: " << uboName 
              << ", size: " << uboSize 
              << ", binding point: " << uboBindingPoint << std::endl;
    shape3D->SetMaterialUBOName(uboName);

    MaterialProperties3D materialProps;
    materialProps.ambient = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f); // Example ambient color
    materialProps.diffuse = glm::vec4(1.0f, 0.5f, 0.31f, 1.0f); // Example diffuse color
    materialProps.specular = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f); // Example specular color
    materialProps.shininess = 32.0f; // Example shininess


    // Get the shader program
    std::shared_ptr<RavenEngine::ShaderProgram> shaderProgramPtr = shaderManager.GetShader("defaultShader3D");
    if (!shaderProgramPtr) {
        std::cerr << "SHAPECREATE::3D Failed to get valid shader program for: " << defaultShaderName << std::endl;
        return nullptr;
    }

    // Get the GLuint representing the shader program
    GLuint shaderProgram = shaderProgramPtr->GetID();
    if (!shaderProgram || !glIsProgram(shaderProgram)) { // If the shader program is invalid
        std::cerr << "SHAPECREATE::3D Failed to get valid shader program for: " << defaultShaderName << std::endl;
        return nullptr;
    }
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
    ++uniqueID;

    return shape3D;
}
} // namespace RavenEngine