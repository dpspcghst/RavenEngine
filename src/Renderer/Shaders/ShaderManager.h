// shadermanager.h
#pragma once

// #include section
// #####################
// Standard library includes
#include <map>
#include <string>
#include <memory> 
// Third party includes

// Raven includes
#include "ShaderProgram.h"
#include "../UBO/UniformBufferManager.h"

namespace RavenEngine {

class ShaderManager {
public:
    static ShaderManager& GetInstance();

    void LoadShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    bool IsShaderLoaded(const std::string& name) const;
    std::shared_ptr<ShaderProgram> GetShader(const std::string& name) const;
    void UseShader(const std::string& name);

    void PrintAllShaderInfo();

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;

private:
    ShaderManager();
    ~ShaderManager();

    std::map<std::string, std::shared_ptr<ShaderProgram>> shaders; // Use shared_ptr for automatic memory management
    UniformBufferManager& uniformBufferManager = UniformBufferManager::GetInstance();
};

} // namespace RavenEngine
