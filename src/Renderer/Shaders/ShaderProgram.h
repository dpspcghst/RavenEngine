// shaderprogram.h
#pragma once

// #include section
// #####################
// Standard library includes
#include <string>

// Third party includes
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace RavenEngine {

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    // Load and compile shaders from source strings, and link them into a program
    bool LoadFromSource(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);

    // Use this shader program for rendering
    void Use() const;

    void SetAlpha(float alpha);

    // Set uniform functions
    void SetUniform(const std::string& name, const glm::mat4& value);
    void SetUniform(const std::string& name, const glm::vec4& value);
    void SetUniform(const std::string& name, int value);
    void SetUniform(const std::string& name, float value);

    GLuint GetUniformBlockIndex(const std::string& blockName) const;

    // Get the ID of the shader program
    GLuint GetID() const;

    // Utility methods
    GLint GetUniformLocation(const std::string& name) const;
    GLint GetAttributeLocation(const std::string& name) const;

private:
    GLuint id; // ID of the shader program

    // Utility methods
    bool CompileShader(GLuint& shaderID, GLenum type, const std::string& source);
    bool LinkProgram();
    void CheckCompileErrors(GLuint shaderID, const std::string& type) const;
    void CheckLinkErrors() const;
};

} // namespace RavenEngine
