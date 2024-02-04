// MaterialProperties.h
#ifndef MATERIAL_PROPERTIES_H
#define MATERIAL_PROPERTIES_H

// #include section
// #####################
// Third party includes
#include <glm/glm.hpp>

namespace RavenEngine {

struct MaterialProperties {
    glm::vec4 color; 

    bool operator!=(const MaterialProperties& other) const {
        return color != other.color;
    }
};

} // namespace RavenEngine

#endif // MATERIAL_PROPERTIES_H