#include "ShaderManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace RavenEngine {

ShaderManager::ShaderManager() {
    shaders = std::map<std::string, GLuint>();
    //std::cout << "ShaderManager constructor called" << std::endl;
}

ShaderManager& ShaderManager::GetInstance() {
    //std::cout << "ShaderManager GetInstance called" << std::endl;
    static ShaderManager instance;
    return instance;
}

ShaderManager::~ShaderManager() {
    std::cout << "ShaderManager destructor called" << std::endl;
    for (auto& shader : shaders) {
        glDeleteProgram(shader.second);
    }
}

// Load shader method
bool ShaderManager::LoadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    //std::cout << "Loading shader: " << name << std::endl;

    std::string vertexCode = ReadShaderFile(vertexShaderPath);
    std::string fragmentCode = ReadShaderFile(fragmentShaderPath);

    GLuint shaderProgram = CreateShader(vertexCode, fragmentCode);
    if (shaderProgram == 0) {
        std::cerr << "Failed to create shader program: " + name << std::endl;
        return false;
    }

    shaders[name] = shaderProgram;
    return true;
}

GLuint ShaderManager::GetShader(const std::string& name) {              // Get shader method
    //std::cout << "get shader called" << std::endl;
    auto it = shaders.find(name); // Find the shader in the shaders map
    if (it == shaders.end()) {
        throw std::runtime_error("Shader not found: " + name);
    }
    return it->second;
}

std::string ShaderManager::GetShaderName(GLuint shaderID) {             // Get shader name
    //std::cout << "get shader name called" << std::endl;

    for (const auto& shader : shaders) { // For each shader in the shaders map
        if (shader.second == shaderID) { // If the shader ID matches the shader ID passed in
            return shader.first; // Return the shader name
        }
    }
    return ""; // Return an empty string if the shader was not found (this requires the calling code to check for an empty string)
}

GLuint ShaderManager::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    //std::cout << "create shader called" << std::endl;

    // Create the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexSource = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    CheckShaderCompileError(vertexShader, "VERTEX");

    // Create the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentSource = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    CheckShaderCompileError(fragmentShader, "FRAGMENT");

    // Create the shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for shader program linking errors
    CheckProgramLinkError(shaderProgram);

    // Delete the shaders as they're linked into the program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::string ShaderManager::ReadShaderFile(const std::string& filePath) {

    std::ifstream shaderFile(filePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Unable to open shader file: " << filePath << std::endl;
        return "";
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();

    std::string shaderContent = shaderStream.str();
    //std::cout << "Shader content: " << shaderContent << std::endl; // print the shader content

    return shaderContent;
}

void ShaderManager::UseShader(const std::string& name) {
    //std::cout << "use shader called" << std::endl;

    GLuint shader = GetShader(name);
    if (shader == 0) {
        std::cerr << "Failed to use shader: " + name << std::endl;
        return;
    }
    glUseProgram(shader);
}

void ShaderManager::SetMatrix4(const std::string& shaderName, const std::string& name, const glm::mat4& value) {


    //std::cout << "set matrix 4 called" << std::endl;
    GLuint shader = GetShader(shaderName);
    if (shader == 0) {
        std::cerr << "Failed to find shader: " + shaderName << std::endl;
        return;
    }
    glUseProgram(shader);
    GLint uniformLocation = glGetUniformLocation(shader, name.c_str());
    if (uniformLocation == -1) {
        std::cerr << "Uniform '" + name + "' not found in shader program: " + shaderName << std::endl;
        return;
    }
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderManager::CheckShaderCompileError(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

void ShaderManager::CheckProgramLinkError(GLuint program) {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM_LINKING_ERROR: \n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

void ShaderManager::PrintAllShaderInfo() {
    //std::cout << "Total shaders loaded: " << shaders.size() << std::endl;
    for (const auto& shader : shaders) {
        //std::cout << "Shader name: " << shader.first << ", Program ID: " << shader.second << std::endl;
    }
}

} // End of RavenEngine namespace
