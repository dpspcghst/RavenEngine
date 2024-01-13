#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace RavenEngine {

class Line {
public:
    Line(const glm::vec3& startPoint, const glm::vec3& endPoint);
    ~Line();

    void Create(); // Set up the line data
    void Render(); // Render the line
    void TestLine(); // Test the line

private:
    glm::vec3 start;
    glm::vec3 end;
    unsigned int VAO;
    unsigned int VBO;
};

} // namespace RavenEngine
