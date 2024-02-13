// Circle.h
// #####################
#pragma once
// #####################
// #include section
// #####################
// Standard library includes

// Third-party includes
#include <glad/glad.h>
#include <glm/glm.hpp>
// Raven includes
#include "Shape2D.h"

namespace RavenEngine {
    class Circle : public Shape2D {
    public:
        Circle();
        Circle(float radius, int segments);
        virtual ~Circle();

        void Create() override;
        void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;
        int GetVertexCount() const override;

        // Add a method to set the texture ID
        void SetTextureId(int id) { textureId = id; }
        // Add a method to get the texture ID
        int GetTextureId() const { return textureId; }

    private:
        struct Vertex {
            glm::vec3 position;
            glm::vec2 texCoords; // Even though Circle might not use texCoords, it maintains consistency.
        };

        float radius;
        int segments;
        std::vector<Vertex> vertices; // Use a dynamic array to store vertices dynamically based on segments

        // Add a member variable to store the texture ID
        int textureId;

        void CalculateVertices(); // A helper function to calculate vertices based on radius and segments
    };
} // namespace RavenEngine