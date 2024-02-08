// shaderloader.h
#pragma once
// #include section
// #####################
// Standard library includes
#include <string>

namespace RavenEngine {

class ShaderLoader {
public:
    // Constructor
    ShaderLoader() = default;

    // Destructor
    ~ShaderLoader() = default;

    // Disable copy and move semantics
    ShaderLoader(const ShaderLoader&) = delete;
    ShaderLoader& operator=(const ShaderLoader&) = delete;

    // Read shader source code from a file
    static std::string ReadShaderFile(const std::string& filePath);
};

} // namespace RavenEngine
