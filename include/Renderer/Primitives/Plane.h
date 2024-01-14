// Plane.h
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp> // Include this for glm::vec2

namespace RavenEngine {

class Plane {
public:
    Plane();
    ~Plane();

    void Create();
    void Render();
    void SetSize(float width, float height); // Declare the SetSize method
    void SetPosition(float x, float y); // Declare the SetPosition method
    glm::vec2 GetSize() const { return size; } // Add this line

private:
    GLuint VAO, VBO;
    glm::vec2 size; // Declare a size member variable
    glm::vec2 position; // Declare a position member variable
};

} // namespace RavenEngine