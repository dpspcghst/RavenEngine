#include "ShaderManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

namespace RavenEngine {

ShaderManager::ShaderManager() {}

ShaderManager::~ShaderManager() {
    for (auto& shader : shaders) {
        glDeleteProgram(shader.second);
    }
}

bool ShaderManager::LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexCode = ReadShaderFile(vertexPath);
    std::string fragmentCode = ReadShaderFile(fragmentPath);

    GLuint shaderProgram = CreateShader(vertexCode, fragmentCode);
    if (shaderProgram == 0) {
        std::cerr << "Failed to create shader program: " << name << std::endl;
        return false;
    }

    shaders[name] = shaderProgram;
    return true;
}

GLuint ShaderManager::GetShader(const std::string& name) {
    auto it = shaders.find(name);
    if (it != shaders.end()) {
        return it->second;
    } else {
        std::cerr << "Shader not found: " << name << std::endl;
        return 0;
    }
}

std::string ShaderManager::GetShaderName(GLuint shaderID) {
    for (const auto& shader : shaders) {
        if (shader.second == shaderID) {
            return shader.first;
        }
    }
    return "";
}


GLuint ShaderManager::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    // Add error checking here

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    // Add error checking here

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Add error checking here for shader program linking

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::string ShaderManager::ReadShaderFile(const std::string& filePath) {
    std::ifstream shaderFile(filePath);
    if (!shaderFile) {
        std::cerr << "Unable to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    return shaderStream.str();
}

void ShaderManager::UseShader(const std::string& name) {
    GLuint shader = GetShader(name);
    if (shader != 0) {
        glUseProgram(shader);
    }
}

void ShaderManager::SetUniform(const std::string& name, const glm::mat4& value) {
    GLuint currentShader;
    glGetIntegerv(GL_CURRENT_PROGRAM, reinterpret_cast<GLint*>(&currentShader));
    GLint uniformLocation = glGetUniformLocation(currentShader, name.c_str());
    if (uniformLocation != -1) {
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
    } else {
        std::cerr << "Uniform '" << name << "' not found in the current shader program" << std::endl;
    }
}

} // End of RavenEngine namespace