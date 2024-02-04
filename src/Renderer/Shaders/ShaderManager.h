// shadermanager.h
#pragma once

// #include section
// #####################
// standard library includes
#include <map>
#include <string>
#include <vector>
// third party includes
#include <glad/glad.h>
#include <glm/glm.hpp>

// Raven includes
#include "../../src/Renderer/UBO/UniformBuffer.h"

namespace RavenEngine {

class ShaderManager {
public:
    static ShaderManager& GetInstance();

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

    bool LoadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    GLuint GetShader(const std::string& name);
    std::string GetShaderName(GLuint shaderID);
    bool UseShader(const std::string& name);
    void SetMatrix4(const std::string& shaderName, const std::string& name, const glm::mat4& value);

    void SetUniformVec4(const std::string& shaderName, const std::string& name, const glm::vec4& value);
    void SetUniformInt(const std::string& shaderName, const std::string& name, int value);
    void SetUniformFloat(const std::string& shaderName, const std::string& name, float value);

    GLint GetAttributeLocation(const std::string& shaderName, const std::string& attributeName);
    
    // New method to create a UBO
    void CreateUniformBuffer(const std::string& name, size_t size, unsigned int bindingPoint);
    
    // New method to update a UBO
    void UpdateUniformBuffer(const std::string& name, const void* data, size_t size, size_t offset = 0);
    
    // New method to bind a UBO
    void BindUniformBuffer(const std::string& name);
    void UnbindUniformBuffer(const std::string& name);
    bool IsShaderLoaded(const std::string& name) {
        return shaders.count(name) > 0;
    }

    // New methods
    bool IsShaderBeingUsed(const std::string& shaderName);
    bool IsUBOBound(const std::string& uboName);
    UniformBufferProperties GetUBOProperties(const std::string& uboName);
    void GetUBOData(const std::string& name, void* data, size_t size, size_t offset = 0);
    std::vector<std::string> GetUniformBufferNames() const;


    void PrintAllShaderInfo();

private:
    ShaderManager();
    ~ShaderManager();

    GLuint CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    std::string ReadShaderFile(const std::string& filePath);
    void CheckShaderCompileError(GLuint shader, const std::string& type);
    void CheckProgramLinkError(GLuint program);

    std::map<std::string, GLuint> shaders;
    std::map<std::string, UniformBuffer> uniformBuffers; 

    // New member variables
    std::string currentShaderName;
    std::string currentUBOName;
    GLuint lastBoundUBO = 0;
};

} // End of RavenEngine namespace