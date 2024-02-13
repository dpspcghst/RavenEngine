// shadermanager.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
// Third party includes

// Raven includes
#include "ShaderManager.h"
#include "ShaderLoader.h"
#include "ShaderProgram.h"
#include "../UBO/UniformBufferManager.h"

namespace RavenEngine {

ShaderManager::ShaderManager() {
    // Initialization if needed
}

ShaderManager& ShaderManager::GetInstance() {
    static ShaderManager instance;
    return instance;
}

ShaderManager::~ShaderManager() {
    // Cleanup if needed, though individual shaders are managed by ShaderProgram now
}

void ShaderManager::LoadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    ShaderLoader loader;
    std::string vertexCode = loader.ReadShaderFile(vertexShaderPath);
    std::string fragmentCode = loader.ReadShaderFile(fragmentShaderPath);

    // Log shader source code
    // std::cout << "Vertex shader source code for " << name << ":\n" << vertexCode << std::endl;
    // std::cout << "Fragment shader source code for " << name << ":\n" << fragmentCode << std::endl;

    auto shaderProgram = std::make_shared<ShaderProgram>();
    if (shaderProgram->LoadFromSource(vertexCode, fragmentCode)) {
        shaders[name] = shaderProgram;
         std::cout << "SHADERMANAGER::LOADSHADER Shader loaded and compiled: " << name << std::endl;

        // Check for OpenGL errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            std::cerr << "OpenGL error occurred after loading shader " << name << ": " << error << std::endl;
        }
    } else {
        std::cerr << "Failed to load shader: " << name << std::endl;
    }
}

bool ShaderManager::IsShaderLoaded(const std::string& name) const {
    return shaders.find(name) != shaders.end();
    // print to console
    std::cout << "SHADERMANAGER::ISSHADERLOADED Shader loaded: " << name << std::endl;
}

std::shared_ptr<ShaderProgram> ShaderManager::GetShader(const std::string& name) const {
    auto it = shaders.find(name);
    if (it != shaders.end()) {
        //std::cout << "SHADERMANAGER::GETSHADER Found shader: " << name << std::endl;
        return it->second;
    } else {
        std::cerr << "Shader not found: " << name << std::endl;
        return nullptr;
    }
}

void ShaderManager::UseShader(const std::string& name) {
    auto shaderProgram = GetShader(name);
    if (shaderProgram) {
        shaderProgram->Use();
        std::cout << "SHADERMANAGER::USESHADER Using shader: " << name << std::endl;
    } else {
        std::cerr << "Failed to use shader: " << name << " - shader not found." << std::endl;
    }
}

// Remove functions related to direct shader file reading, compilation, and linking,
// uniform setting, and uniform buffer management as they're now handled by ShaderProgram and UniformBufferManager.

} // namespace RavenEngine
