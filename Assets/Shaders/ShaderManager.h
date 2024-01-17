#ifndef RAVENENGINE_SHADERMANAGER_H
#define RAVENENGINE_SHADERMANAGER_H

#include <string>
#include <map>
#include <glad/glad.h> // Use GLAD for OpenGL functions
#include <glm/glm.hpp>

namespace RavenEngine {

class ShaderManager {
public:
    ShaderManager();
    ~ShaderManager();

    bool LoadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    GLuint GetShader(const std::string& name);
    std::string GetShaderName(GLuint shaderID);
    void UseShader(const std::string& name);
    void SetUniform(const std::string& name, const glm::mat4& value);

private:
    std::map<std::string, GLuint> shaders;

    GLuint CreateShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
    std::string ReadShaderFile(const std::string& filePath);
};

} // End of RavenEngine namespace

#endif // RAVENENGINE_SHADERMANAGER_H
