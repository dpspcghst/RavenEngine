// ShaderLoader.cpp
#include "ShaderLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace RavenEngine {

std::string ShaderLoader::ReadShaderFile(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Unable to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    // Optionally, might want to log the shader content for debugging purposes,
    // but consider that it might clutter the console output with large shader sources.
    // std::cout << "Shader content: " << shaderStream.str() << std::endl;

    return shaderStream.str();
}

} // namespace RavenEngine
