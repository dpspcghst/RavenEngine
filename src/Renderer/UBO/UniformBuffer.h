#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

#include <string>
#include <glm/glm.hpp>

namespace RavenEngine {

struct UniformBufferProperties {
    size_t size;
    unsigned int bindingPoint;
    GLuint bufferID;
};

class UniformBuffer {
public:
    // Constructor & Destructor
    explicit UniformBuffer(size_t size, unsigned int bindingPoint);
    ~UniformBuffer() = default;

    // Public Methods
    void Bind() const;
    void Unbind() const;
    void Update(const void* data, size_t size, size_t offset = 0);
    void GetData(void* data, size_t size, size_t offset = 0) const;
    void UpdateColor(const glm::vec4& color);

    // Getters
    size_t GetSize() const;
    unsigned int GetID() const;
    UniformBufferProperties GetProperties() const;

private:
    // Helper Methods
    bool LogGLError(const std::string& functionName) const;
    void CheckBufferBinding(GLuint expectedBindingPoint) const;

    // Member Variables
    GLuint bufferID;
    GLuint bindingPoint;
    size_t bufferSize;
};

} // namespace RavenEngine

#endif // UNIFORM_BUFFER_H
