#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <string>
#include <unordered_map>
#include <glad/glad.h>

namespace RavenEngine {

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();

    bool LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    GLuint GetShader(const std::string& name);

private:
    std::unordered_map<std::string, GLuint> shaders;

    GLuint CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    std::string ReadShaderFile(const std::string& filePath);
};

} // namespace RavenEngine

#endif // SHADER_MANAGER_H
