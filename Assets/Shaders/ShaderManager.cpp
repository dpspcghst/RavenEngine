#include "ShaderManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace RavenEngine;

ShaderManager::ShaderManager() {}

ShaderManager::~ShaderManager() {
    // Delete all shaders
    for (auto& shader : shaders) {
        glDeleteProgram(shader.second);
    }
}

bool ShaderManager::LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = ReadShaderFile(vertexPath);
    std::string fragmentCode = ReadShaderFile(fragmentPath);

    GLuint shaderProgram = CreateShader(vertexCode, fragmentCode);
    if (shaderProgram == 0) {
        return false;
    }

    shaders[name] = shaderProgram;
    return true;
}

GLuint ShaderManager::GetShader(const std::string& name) {
    return shaders[name];
}

GLuint ShaderManager::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    // Vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    // Check for compile errors...
    // Fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    // Check for compile errors...
    // Link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Check for linking errors...

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::string ShaderManager::ReadShaderFile(const std::string& filePath) {
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    shaderFile.open(filePath);
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}
