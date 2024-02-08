// UniformBufferManager.h
#ifndef UNIFORM_BUFFER_MANAGER_H
#define UNIFORM_BUFFER_MANAGER_H

#include "UniformBuffer.h"
#include <map>
#include <string>

namespace RavenEngine {

class UniformBufferManager {
public:
    static UniformBufferManager& GetInstance() {
        static UniformBufferManager instance; // Guaranteed to be destroyed, instantiated on first use.
        return instance;
    }

    // Delete copy constructor and assignment operator
    UniformBufferManager(const UniformBufferManager&) = delete;
    UniformBufferManager& operator=(const UniformBufferManager&) = delete;

    void CreateUniformBuffer(const std::string& name, size_t size, unsigned int bindingPoint);
    void UpdateUniformBuffer(const std::string& name, const void* data, size_t size, size_t offset = 0);
    void BindUniformBuffer(const std::string& name);
    void UnbindUniformBuffer(const std::string& name);
    UniformBufferProperties GetUBOProperties(const std::string& uboName) const;
    void GetUBOData(const std::string& name, void* data, size_t size, size_t offset = 0);


private:
    UniformBufferManager() = default; // Make constructor private
    ~UniformBufferManager(); // Implement to ensure proper cleanup of UniformBuffers

    std::map<std::string, UniformBuffer> uniformBuffers;
};

} // namespace RavenEngine

#endif // UNIFORM_BUFFER_MANAGER_H