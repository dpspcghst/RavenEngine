// UniformBuffer.h
#ifndef UNIFORM_BUFFER_H
#define UNIFORM_BUFFER_H

// #include section
// #####################
// standard library includes
#include <string>

// third party includes
#include <glad/glad.h>
#include <glm/glm.hpp> 

namespace RavenEngine {

struct UniformBufferProperties {
    size_t size;
    unsigned int bindingPoint;
    GLuint bufferID;
};

class UniformBuffer {
public:
    UniformBuffer(size_t size, unsigned int bindingPoint);              // Initializes a new Uniform Buffer Object with the given size and binding point
    ~UniformBuffer() = default;                                         // Default destructor

    void Bind() const;                                                  // Binds the Uniform Buffer Object to the GL_UNIFORM_BUFFER target
    void Unbind() const;                                                // Unbinds the current Uniform Buffer Object from the GL_UNIFORM_BUFFER target
    void Update(const void* data, size_t size, size_t offset = 0);      // Updates the data in the Uniform Buffer Object
    void GetData(void* data, size_t size, size_t offset = 0) const;     // Retrieves data from the Uniform Buffer Object

    size_t GetSize() const;                                             // Returns the size of the Uniform Buffer Object

    UniformBufferProperties GetProperties() const;                      // Returns the properties of the Uniform Buffer Object

    unsigned int GetID() const;                                         // Returns the ID of the Uniform Buffer Object

    // Declare the UpdateColor method
    void UpdateColor(const glm::vec4& color);

private:
    bool LogGLError(const std::string& functionName) const;             // Checks for OpenGL errors and logs them if any are found
    void CheckBufferBinding(GLuint bindingPoint) const;                 // Checks if the Uniform Buffer Object is correctly bound to the expected binding point

    unsigned int bufferID;                                              // The ID of the Uniform Buffer Object
    unsigned int bindingPoint;                                          // The binding point of the Uniform Buffer Object
    size_t bufferSize;                                                  // The size of the Uniform Buffer Object
};

} // namespace RavenEngine

#endif // UNIFORM_BUFFER_H