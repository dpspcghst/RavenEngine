// Mesh.h
#pragma once

#include <glad/glad.h>
#include <vector>
#include <string> // Include the string header

namespace RavenEngine {

class Mesh {
public:
    Mesh(); // Constructor
    ~Mesh(); // Destructor

    void LoadFromFile(const std::string& filename); // Load mesh data from a file
    void GenerateVAO(); // Generate the VAO for the mesh

    GLuint GetVAO() const { return VAO; } // Get the VAO of the mesh
    size_t GetVertexCount() const { return vertices.size(); } // Get the vertex count of the mesh

private:
    std::vector<float> vertices; // Vertex data
    GLuint VAO; // Vertex Array Object
};

} // namespace RavenEngine