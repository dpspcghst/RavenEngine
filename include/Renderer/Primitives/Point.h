#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp> // Include GLM (for vec3)

namespace RavenEngine {

class Point {
public:
    explicit Point(const glm::vec3& position);
    ~Point();

    void Create(); // Set up the point data
    void Render(); // Render the point

private:
    glm::vec3 position; // Coordinates of the point
    unsigned int VAO, VBO; // Vertex Array Object, Vertex Buffer Object
};

} // namespace RavenEngine
