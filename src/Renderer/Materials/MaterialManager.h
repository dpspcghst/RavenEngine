// MaterialManager.h
#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

// #include section
// #####################

// Standard library includes
#include <map>
#include <string>
#include <sstream>

// Raven includes
#include "MaterialProperties.h" // Include MaterialProperties

namespace RavenEngine {

class MaterialManager {
public:
    // Create a map to store UBOs, where the key is a string representing the material properties.
    std::map<std::string, std::string> uboMap;

    std::string GenerateKeyFromMaterialProperties(const MaterialProperties& props);

    // Add other methods for managing materials as needed
};

} // namespace RavenEngine

#endif // MATERIAL_MANAGER_H