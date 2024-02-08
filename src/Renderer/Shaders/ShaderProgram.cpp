// ShaderProgram.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>
#include <vector>
// Third party includes
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
// Raven includes
#include "ShaderProgram.h"

namespace RavenEngine {

ShaderProgram::ShaderProgram() : id(0) {
}

ShaderProgram::~ShaderProgram() {
    if (id != 0) {
        glDeleteProgram(id);
    }
}

bool ShaderProgram::LoadFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
    GLuint vertexShader, fragmentShader;
    if (!CompileShader(vertexShader, GL_VERTEX_SHADER, vertexShaderSource)) return false;
    if (!CompileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource)) return false;

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    bool linkSuccess = LinkProgram();
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return linkSuccess;
}

void ShaderProgram::Use() const {
    if (id != 0) {
        glUseProgram(id);
        std::cout << "SHADERPROGRAM::USE Using shader program with ID: " << id << std::endl;
    } else {
        std::cout << "SHADERPROGRAM::USE Shader program ID is zero" << std::endl;
    }
}

void ShaderProgram::SetUniform(const std::string& name, const glm::mat4& value) {
    GLint loc = glGetUniformLocation(id, name.c_str());
    if (loc != -1) {
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
        //std::cout << "SHADERPROGRAM::SETUNIFORM Setting uniform " << name << " to " << glm::to_string(value) << std::endl;
    } else {
        std::cout << "SHADERPROGRAM::SETUNIFORM Uniform " << name << " location is -1" << std::endl;
    }
}

void ShaderProgram::SetUniform(const std::string& name, const glm::vec4& value) {
    GLint loc = glGetUniformLocation(id, name.c_str());
    if (loc != -1) {
        glUniform4fv(loc, 1, glm::value_ptr(value));
    }
}

void ShaderProgram::SetUniform(const std::string& name, int value) {
    GLint loc = glGetUniformLocation(id, name.c_str());
    if (loc != -1) {
        glUniform1i(loc, value);
    }
}

void ShaderProgram::SetUniform(const std::string& name, float value) {
    GLint loc = glGetUniformLocation(id, name.c_str());
    if (loc != -1) {
        glUniform1f(loc, value);
    }
}

GLuint ShaderProgram::GetUniformBlockIndex(const std::string& blockName) const {
    if (id == 0) {
        std::cerr << "ShaderProgram::GetUniformBlockIndex: Shader program ID is zero." << std::endl;
        return GL_INVALID_INDEX;
    }
    GLuint blockIndex = glGetUniformBlockIndex(id, blockName.c_str());
    if (blockIndex == GL_INVALID_INDEX) {
        std::cerr << "ShaderProgram::GetUniformBlockIndex: Uniform block '" << blockName << "' not found." << std::endl;
    }
    return blockIndex;
}

GLuint ShaderProgram::GetID() const {
    return id;
}

GLint ShaderProgram::GetUniformLocation(const std::string& name) const {
    return glGetUniformLocation(id, name.c_str());
}

GLint ShaderProgram::GetAttributeLocation(const std::string& name) const {
    return glGetAttribLocation(id, name.c_str());
}

bool ShaderProgram::CompileShader(GLuint& shaderID, GLenum type, const std::string& source) {
    shaderID = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        CheckCompileErrors(shaderID, type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
        return false;
    }
    // Debug print
    std::cout << "SHADERPROGRAM::COMPILESHADER Compilation successful for " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader with ID: " << shaderID << std::endl;

    return true;
}

bool ShaderProgram::LinkProgram() {
    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        CheckLinkErrors();
        return false;
    }
    std::cout << "SHADERPROGRAM::LINKPROGRAM Linking successful for program with ID: " << id << std::endl;

    return true;
}

void ShaderProgram::CheckCompileErrors(GLuint shaderID, const std::string& type) const {
    GLint maxLength = 0;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderID, maxLength, &maxLength, &errorLog[0]);

    std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << &errorLog[0] << "\n -- --------------------------------------------------- -- " << std::endl;
}

void ShaderProgram::CheckLinkErrors() const {
    GLint maxLength = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

    std::vector<GLchar> errorLog(maxLength);
    glGetProgramInfoLog(id, maxLength, &maxLength, &errorLog[0]);

    std::cerr << "ERROR::PROGRAM_LINKING_ERROR: \n" << &errorLog[0] << "\n -- --------------------------------------------------- -- " << std::endl;
}

} // namespace RavenEngine
