// line.h
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
    class Line : public Shape2D {
    public:
        Line(); // Default constructor
        Line(const glm::vec3& startPoint, const glm::vec3& endPoint);
        virtual ~Line();

        void Create() override;
        void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const override;

        int GetVertexCount() const override;

        // Add a method to set the texture ID
        void SetTextureId(int id) { textureId = id; }
        // Add a method to get the texture ID
        int GetTextureId() const { return textureId; }

    private:
        glm::vec3 start{0.0f, 0.0f, 0.0f}, end{0.0f, 0.0f, 0.0f}; // Initialize to default values
        GLuint VAO = 0, VBO = 0;

        // Add a member variable to store the texture ID
        int textureId;
    };
} // namespace RavenEngine