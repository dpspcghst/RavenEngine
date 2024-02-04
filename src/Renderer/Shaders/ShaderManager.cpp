// shadermanager.cpp

// #include section
// #####################
// Standard library includes
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
// Third party includes
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
// Raven includes
#include "ShaderManager.h"
#include "../Materials/MaterialProperties.h"

namespace RavenEngine {

// Construct/Instance/Destruct
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

// Create/Load/Get/Read/Use
GLuint ShaderManager::CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
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
    std::cout << "SHADERMANAGER::CREATESHADER program created with ID: " << shaderProgram << std::endl;

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Bind the attribute location
    glBindAttribLocation(shaderProgram, 0, "aPos");

    glLinkProgram(shaderProgram);

    // Check for shader program linking errors
    CheckProgramLinkError(shaderProgram);

    // Validate the shader program
    glValidateProgram(shaderProgram);
    GLint validationStatus;
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &validationStatus);
    if (validationStatus == GL_FALSE) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "Shader program validation error: " << infoLog << std::endl;
    }

    // Delete the shaders as they're linked into the program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //std::cout << "SHADERMANAGER::CREATESHADER Shader program linked with ID: " << shaderProgram << std::endl;

    return shaderProgram;
}

bool ShaderManager::LoadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
    //std::cout << "Loading shader: " << name << std::endl;

    std::string vertexCode = ReadShaderFile(vertexShaderPath);
    std::string fragmentCode = ReadShaderFile(fragmentShaderPath);

    GLuint shaderProgram = CreateShader(vertexCode, fragmentCode);
    if (shaderProgram == 0) {
        std::cerr << "Failed to create shader program: " + name << std::endl;
        return false;
    }

    std::cout << "SHADERMANAGER::LOADSHADER program loaded with ID: " << shaderProgram << " for shader: " << name << std::endl;

    shaders[name] = shaderProgram;

    std::cout << "SHADERMANAGER::LOADSHADER program with ID: " << shaders[name] << " added to shaders map for shader: " << name << std::endl;

    return true;
}

GLuint ShaderManager::GetShader(const std::string& name) {
    // Check if the shader program exists
    if (shaders.find(name) == shaders.end()) {
        //std::cout << "SHADERMANAGER::GETSHADER Shader program with name " << name << " does not exist." << std::endl;
        return 0;
    }

    GLuint shaderProgram = shaders[name];

    // Check if the shader program ID is valid
    if (glIsProgram(shaderProgram) == GL_FALSE) {
        std::cout << "if (glIsProgram()) Shader program with ID " << shaderProgram << " is not valid." << std::endl;
        return 0;
    }

    //std::cout << "SHADERMANAGAGER::GETSHADER Retrieved shader program with ID " << shaderProgram << std::endl;
    return shaderProgram;
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

bool ShaderManager::IsShaderBeingUsed(const std::string& shaderName) {
    return currentShaderName == shaderName;
}

bool ShaderManager::UseShader(const std::string& name) {
    //std::cout << "use shader called" << std::endl;

    GLuint shader = GetShader(name);
    if (shader == 0) {
        std::cerr << "Failed to use shader: " + name << std::endl;
        return false;
    }
    glUseProgram(shader);
    return true;
}

// Set a mat4 uniform in the shader
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

// Set a vec4 uniform in the shader
void ShaderManager::SetUniformVec4(const std::string& shaderName, const std::string& name, const glm::vec4& value) {
    GLuint shader = GetShader(shaderName);
    if (shader == 0) {
        std::cerr << "Failed to find shader: " + shaderName << std::endl;
        return;
    }
    glUseProgram(shader); // Ensure the shader is active
    GLint uniformLocation = glGetUniformLocation(shader, name.c_str());
    if (uniformLocation == -1) {
        std::cerr << "Uniform '" + name + "' not found in shader program: " + shaderName << std::endl;
        return;
    }
    glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
}

// Set an int uniform in the shader
void ShaderManager::SetUniformInt(const std::string& shaderName, const std::string& name, int value) {
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
    glUniform1i(uniformLocation, value);
}

// Set a float uniform in the shader
void ShaderManager::SetUniformFloat(const std::string& shaderName, const std::string& name, float value) {
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
    glUniform1f(uniformLocation, value);
}

void ShaderManager::PrintAllShaderInfo() {
    //std::cout << "Total shaders loaded: " << shaders.size() << std::endl;
    for (const auto& shader : shaders) {
        //std::cout << "Shader name: " << shader.first << ", Program ID: " << shader.second << std::endl;
    }
}

bool ShaderManager::IsUBOBound(const std::string& uboName) {
    return currentUBOName == uboName;
}

void ShaderManager::GetUBOData(const std::string& name, void* data, size_t size, size_t offset) {
    auto it = uniformBuffers.find(name);
    if (it != uniformBuffers.end()) {
        it->second.GetData(data, size, offset);
    } else {
        std::cerr << "ShaderManager::GetUBOData UBO name not found: " << name << std::endl;
    }
}

void ShaderManager::CreateUniformBuffer(const std::string& name, size_t size, unsigned int bindingPoint) {
    for (auto& pair : uniformBuffers) {
        if (pair.second.GetProperties().bindingPoint == bindingPoint) {
            std::cerr << "SHADERMANAGER::CREATEUNIFORMBUFFER Error: Binding point " << bindingPoint << " is already in use." << std::endl;
            return;
        }
    }

    uniformBuffers.emplace(std::make_pair(name, UniformBuffer(size, bindingPoint)));
    std::cout << "SHADERMANAGER::CREATEUNIFORMBUFFER Uniform buffer created with name: " << name << ", size: " << size << ", binding point: " << bindingPoint << std::endl;
}

void ShaderManager::UpdateUniformBuffer(const std::string& name, const void* data, size_t size, size_t offset) {
    auto it = uniformBuffers.find(name);
    if (it == uniformBuffers.end()) {
        std::cerr << "Error: UBO " << name << " not found." << std::endl;
        return;
    }
    
    it->second.Update(data, size, offset);
}


void ShaderManager::BindUniformBuffer(const std::string& name) {
    auto it = uniformBuffers.find(name);
    if (it != uniformBuffers.end()) {
        GLuint uboID = it->second.GetID();
        // Check if the UBO ID is valid
        if (!glIsBuffer(uboID)) {
            std::cerr << "Error: UBO ID " << uboID << " is not a valid buffer." << std::endl;
            return;
        }

        if (lastBoundUBO != uboID) {
            glBindBuffer(GL_UNIFORM_BUFFER, uboID);
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                std::cerr << "OpenGL error after glBindBuffer: " << error << std::endl;
                return;
            }
            lastBoundUBO = uboID;
            std::cout << "SHADERMANAGER::BINDUNIFORMBUFFER Binding new UBO with ID: " << uboID << std::endl;
        }
    } else {
        std::cerr << "Uniform buffer not found: " << name << std::endl;
    }
}

void ShaderManager::UnbindUniformBuffer(const std::string& name) {
    auto it = uniformBuffers.find(name);
    if (it != uniformBuffers.end()) {
        auto properties = it->second.GetProperties();
        glBindBufferBase(GL_UNIFORM_BUFFER, properties.bindingPoint, 0);
        currentUBOName.clear();
    } else {
        std::cerr << "SHADERMANAGER::UNBINDUNIFORMBUFFER UBO " << name << " not found.\n";
    }
}

UniformBufferProperties ShaderManager::GetUBOProperties(const std::string& uboName) {
    auto it = uniformBuffers.find(uboName);
    if (it == uniformBuffers.end()) {
        std::cerr << "SHADERMANAGER::GETUBOPROPERTIES UBO " << uboName << " not found.\n";
        return UniformBufferProperties(); // Return default UniformBufferProperties
    }

    // Assuming UniformBuffer has a GetProperties method
    return it->second.GetProperties();
}

std::vector<std::string> ShaderManager::GetUniformBufferNames() const {
    std::vector<std::string> names;
    for (const auto& pair : uniformBuffers) {
        names.push_back(pair.first);
    }
    return names;
}



GLint ShaderManager::GetAttributeLocation(const std::string& shaderName, const std::string& attributeName) {
    GLuint shader = GetShader(shaderName);
    if (shader == 0) {
        std::cerr << "Failed to find shader: " + shaderName << std::endl;
        return -1;
    }

    // Validate the shader program
    glValidateProgram(shader);
    GLint validationStatus;
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &validationStatus);
    if (validationStatus == GL_FALSE) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader program validation failed: " << infoLog << std::endl;
        return -1;
    }

    GLint attributeLocation = glGetAttribLocation(shader, attributeName.c_str());
    if (attributeLocation == -1) {
        std::cerr << "Attribute '" + attributeName + "' not found in shader program: " + shaderName << std::endl;
    } else {
        std::cout << "Attribute '" + attributeName + "' found in shader program: " + shaderName 
                  << ", location: " << attributeLocation << std::endl;
    }
    return attributeLocation;
}

std::string GetOpenGLErrorString(GLenum error) {
    switch (error) {
        case GL_INVALID_ENUM: return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
        case GL_INVALID_VALUE: return "GL_INVALID_VALUE: A numeric argument is out of range.";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
        case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
        case GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
        case GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
        default: return "Unknown OpenGL error code.";
    }
}

void ShaderManager::CheckShaderCompileError(GLuint shader, const std::string& type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        GLenum error = glGetError();
        std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog 
                  << "\nOpenGL Error: " << GetOpenGLErrorString(error)
                  << "\n -- --------------------------------------------------- -- " << std::endl;
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

} // End of RavenEngine namespace