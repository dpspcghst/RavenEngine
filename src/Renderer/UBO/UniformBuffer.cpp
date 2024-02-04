// uniformbuffer.cpp
// #include section
// #####################
// standard library includes
#include <iostream>

// third party includes
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

// Raven includes
#include "UniformBuffer.h"

namespace RavenEngine {

UniformBuffer::UniformBuffer(size_t size, unsigned int bindingPoint)        // Initializes a new Uniform Buffer Object with the given size and binding point
    : bindingPoint(bindingPoint), bufferSize(size) {
    glGenBuffers(1, &bufferID);
    std::cout << "UNIFORMBUFFER Generated buffer with ID: " << bufferID << std::endl;
    LogGLError("glGenBuffers");

    glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
    LogGLError("glBindBuffer (1)");

    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    LogGLError("glBufferData");

    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, bufferID);
    if (!LogGLError("glBindBufferBase")) {
        // Only perform the check if no previous error occurred
        CheckBufferBinding(bindingPoint);
    }

    std::cout << "UNIFORMBUFFER:: UniformBuffer created with size: " << size 
              << ", bindingPoint: " << bindingPoint 
              << ", bufferID: " << bufferID << std::endl;

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    LogGLError("glBindBuffer (2)");
}

void UniformBuffer::Bind() const {                                          // Binds the Uniform Buffer Object to the GL_UNIFORM_BUFFER target
    std::cout << "Binding buffer with ID: " << bufferID << std::endl;
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
    LogGLError("UNIFORMBUFFER::BIND");
}

void UniformBuffer::Unbind() const {                                        // Unbinds the current Uniform Buffer Object from the GL_UNIFORM_BUFFER target
    std::cout << "Unbinding buffer with ID: " << bufferID << std::endl;
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    LogGLError("UNIFORMBUFFER::UNBIND");
}

unsigned int UniformBuffer::GetID() const {                                 // Returns the ID of the Uniform Buffer Object
    return bufferID;
}

void UniformBuffer::Update(const void* data, size_t size, size_t offset) {
    if (offset + size > bufferSize || offset < 0 || size < 0) {
        std::cerr << "Error: Invalid offset or size. Data not updated." << std::endl;
        return;
    }
    if (!glIsBuffer(bufferID)) {
        std::cerr << "Error: Invalid buffer ID. Data not updated." << std::endl;
        return;
    }
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
    LogGLError("glBindBuffer (3)");
    
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    LogGLError("glBufferSubData");

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    LogGLError("glBindBuffer (4)");
}

void UniformBuffer::UpdateColor(const glm::vec4& color) {
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
    LogGLError("glBindBuffer (3)");

    // Assuming the color data is at the start of the buffer
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(color));
    LogGLError("glBufferSubData");

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    LogGLError("glBindBuffer (4)");
}

size_t UniformBuffer::GetSize() const {                                     // Returns the size of the Uniform Buffer Object
    return bufferSize;
}

void UniformBuffer::GetData(void* data, size_t size, size_t offset) const { // Retrieves data from the Uniform Buffer Object
    glBindBuffer(GL_UNIFORM_BUFFER, bufferID);
    glGetBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

UniformBufferProperties UniformBuffer::GetProperties() const {              // Returns the properties of the Uniform Buffer Object
    return {bufferSize, bindingPoint, bufferID};
}

bool UniformBuffer::LogGLError(const std::string& functionName) const {     // Checks for OpenGL errors and logs them if any are found
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error after " << functionName << ": " << error << std::endl;
        return true;
    } else {
        //std::cout << functionName << " executed successfully." << std::endl;
        return false;
    }
}

void UniformBuffer::CheckBufferBinding(GLuint expectedBindingPoint) const { // Checks if the Uniform Buffer Object is correctly bound to the expected binding point
    GLint currentBufferID;  // This will hold the buffer ID, not the binding point index
    glGetIntegeri_v(GL_UNIFORM_BUFFER_BINDING, expectedBindingPoint, &currentBufferID);

    if (currentBufferID != bufferID) {
        std::cerr << "Error: UBO with buffer ID " << bufferID 
                  << " not correctly bound to expected binding point " << expectedBindingPoint 
                  << ". Currently bound buffer ID at that point: " << currentBufferID << std::endl;
    } else {
        std::cout << "UniformBuffer::CheckBufferBinding: UBO with buffer ID " << bufferID 
                  << " is correctly bound to binding point " << expectedBindingPoint << std::endl;
    }
}

} // namespace RavenEngine