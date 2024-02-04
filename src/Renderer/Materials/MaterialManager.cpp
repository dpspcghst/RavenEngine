// MaterialManager.cpp

// #include section
// #####################

// Raven includes
#include "MaterialManager.h" // Include MaterialManager

namespace RavenEngine {

std::string MaterialManager::GenerateKeyFromMaterialProperties(const MaterialProperties& props) {
    std::stringstream ss;
    ss << props.color.r << "," << props.color.g << "," << props.color.b << "," << props.color.a;
    // Add more properties to the key as needed
    return ss.str();
}

// Implement other methods for managing materials here

} // namespace RavenEngine