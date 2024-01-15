#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <unordered_map>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace RavenEngine {

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();

    bool LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    void UseShader(const std::string& name);
    void SetUniform(const std::string& name, const glm::mat4& value);

    GLuint GetShader(const std::string& name);

private:
    std::unordered_map<std::string, GLuint> shaders;

    GLuint CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    std::string ReadShaderFile(const std::string& filePath);
};

} // namespace RavenEngine

#endif // SHADER_MANAGER_H