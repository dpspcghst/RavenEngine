#pragma once

#include <map>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace RavenEngine {

class ShaderManager {
public:
    static ShaderManager& GetInstance();

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

    bool LoadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    GLuint GetShader(const std::string& name);
    std::string GetShaderName(GLuint shaderID);
    void UseShader(const std::string& name);
    void SetMatrix4(const std::string& shaderName, const std::string& name, const glm::mat4& value);
    
    void PrintAllShaderInfo();

private:
    ShaderManager();
    ~ShaderManager();

    GLuint CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    std::string ReadShaderFile(const std::string& filePath);
    void CheckShaderCompileError(GLuint shader, const std::string& type);
    void CheckProgramLinkError(GLuint program);

    std::map<std::string, GLuint> shaders;
    
};

} // End of RavenEngine namespace
