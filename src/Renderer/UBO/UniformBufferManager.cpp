// UniformBufferManager.cpp
#include "UniformBufferManager.h"
#include <iostream>

namespace RavenEngine {

UniformBufferManager::~UniformBufferManager() {
    // No explicit cleanup needed if UniformBuffer handles its own OpenGL resource management
}

void UniformBufferManager::CreateUniformBuffer(const std::string& name, size_t size, unsigned int bindingPoint) {
    if (uniformBuffers.find(name) == uniformBuffers.end()) {
        uniformBuffers.emplace(std::make_pair(name, UniformBuffer(size, bindingPoint)));
        //std::cout << "UniformBufferManager: Created buffer '" << name << "' with size " << size << " and binding point " << bindingPoint << std::endl;
    } else {
        std::cerr << "UniformBufferManager: Buffer '" << name << "' already exists." << std::endl;
    }
}

void UniformBufferManager::UpdateUniformBuffer(const std::string& name, const void* data, size_t size, size_t offset) {
    auto it = uniformBuffers.find(name);
    if (it != uniformBuffers.end()) {
        it->second.Update(data, size, offset);
        //std::cout << "UniformBufferManager: Updated buffer '" << name << "' with size " << size << " and offset " << offset << std::endl;
    } else {
        std::cerr << "UniformBufferManager: Buffer '" << name << "' not found." << std::endl;
    }
}

void UniformBufferManager::BindUniformBuffer(const std::string& name) {
    auto it = uniformBuffers.find(name);
    if (it != uniformBuffers.end()) {
        it->second.Bind();
        //std::cout << "UniformBufferManager: Bound buffer '" << name << "'" << std::endl;
    } else {
        std::cerr << "UniformBufferManager: Buffer '" << name << "' not found." << std::endl;
    }
}

void UniformBufferManager::UnbindUniformBuffer(const std::string& name) {
    auto it = uniformBuffers.find(name);
    if (it != uniformBuffers.end()) {
        it->second.Unbind();
        //std::cout << "UniformBufferManager: Unbound buffer '" << name << "'" << std::endl;
    } else {
        std::cerr << "UniformBufferManager: Buffer '" << name << "' not found." << std::endl;
    }
}

UniformBufferProperties UniformBufferManager::GetUBOProperties(const std::string& uboName) const {
    auto it = uniformBuffers.find(uboName);
    if (it != uniformBuffers.end()) {
        return it->second.GetProperties();
    } else {
        std::cerr << "UniformBufferManager: Properties for buffer '" << uboName << "' not found." << std::endl;
        return UniformBufferProperties{};
    }
}

void UniformBufferManager::GetUBOData(const std::string& name, void* data, size_t size, size_t offset) {
    auto it = uniformBuffers.find(name);
    if (it != uniformBuffers.end()) {
        // Ensure the buffer is bound
        glBindBuffer(GL_UNIFORM_BUFFER, it->second.GetID());
        
        // Get data from the buffer
        glGetBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);

        // Optionally, unbind the buffer if no further operations are to be done
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        //std::cout << "UniformBufferManager: Retrieved data from buffer '" << name << "'" << std::endl;
    } else {
        std::cerr << "UniformBufferManager: Buffer '" << name << "' not found." << std::endl;
    }
}

} // namespace RavenEngine
