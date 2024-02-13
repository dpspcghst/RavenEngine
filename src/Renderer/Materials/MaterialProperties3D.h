// MaterialProperties3D.h
#ifndef MATERIAL_PROPERTIES_3D_H
#define MATERIAL_PROPERTIES_3D_H

// #include section
// #####################
// Third party includes
#include <glm/glm.hpp>

namespace RavenEngine {

struct MaterialProperties3D {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    bool operator!=(const MaterialProperties3D& other) const {
        return ambient != other.ambient ||
               diffuse != other.diffuse ||
               specular != other.specular ||
               shininess != other.shininess;
    }
};

} // namespace RavenEngine

#endif // MATERIAL_PROPERTIES_3D_H