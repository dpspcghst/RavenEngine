// Rect.cpp

// #include section
// #####################
// standard library includes
#include <iostream>

// third party includes
#include <glm/gtc/type_ptr.hpp>

// Raven includes
#include "Rect.h"
#include "../../Shaders/ShaderManager.h"

namespace RavenEngine {

Rect::Rect() : Shape2D() {
    type = Type::Rect;
}

Rect::~Rect() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Rect::Create() {
    GLfloat vertices[] = {
        // Positions        // Texture Coords
        -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, // Top Left
         0.5f,  0.5f, 0.0f,  1.0f, 1.0f, // Top Right
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, // Bottom Left
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f  // Bottom Right
    };

    // Create VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Texture Coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Unbind VAO
    glBindVertexArray(0);
}

void Rect::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<RavenEngine::ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());

    if (shaderProgramPtr) {
        GLuint shaderProgramID = shaderProgramPtr->GetID();
        glUseProgram(shaderProgramID);

        // Set the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // Bind VAO and draw Rect
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // Unbind
        glBindVertexArray(0);
    } else {
        std::cerr << "Rect::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}

int Rect::GetVertexCount() const {
    return 4;
}

std::vector<glm::vec3> Rect::GetVertices() const {
    std::vector<glm::vec3> currentVertices;

    // Original local vertices of the rectangle
    std::vector<glm::vec3> localVertices = {
        glm::vec3(-0.5f, 0.5f, 0.0f),  // Top Left
        glm::vec3(0.5f, 0.5f, 0.0f),   // Top Right
        glm::vec3(0.5f, -0.5f, 0.0f),  // Bottom Right
        glm::vec3(-0.5f, -0.5f, 0.0f)  // Bottom Left
    };

    // Transform each vertex by the rectangle's transform matrix
    for (const auto& vertex : localVertices) {
        glm::vec4 transformedVertex = transformMatrix * glm::vec4(vertex, 1.0f);
        // Store the transformed vertex back as vec3
        currentVertices.push_back(glm::vec3(transformedVertex));
    }

    return currentVertices;
}

std::vector<glm::vec2> Rect::GetNormals() const {
    std::vector<glm::vec2> normals;

    // Assuming vertices are stored in an array or can be accessed,
    // and are in order: Top Left, Top Right, Bottom Right, Bottom Left
    std::vector<glm::vec3> currentVertices = GetVertices();

    // Calculate edges based on current vertices
    std::vector<glm::vec2> edges;
    for (int i = 0; i < currentVertices.size(); ++i) {
        glm::vec2 currentEdge = glm::vec2(currentVertices[(i + 1) % currentVertices.size()] - currentVertices[i]);
        edges.push_back(currentEdge);
    }

    // Calculate normals for each edge
    for (const auto& edge : edges) {
        glm::vec2 normal = glm::vec2(-edge.y, edge.x); // Perpendicular to edge
        normal = glm::normalize(normal); // Normalize the normal
        normals.push_back(normal);
    }

    return normals;
}

RavenEngine::Shape2D::Projection RavenEngine::Rect::ProjectOntoAxis(const glm::vec2 &axis) const {
    // For a rectangle, the projection onto an axis is a line segment defined by
    // the projections of the rectangle's vertices onto the axis.
    std::vector<glm::vec3> currentVertices = GetVertices();
    float proj1 = glm::dot(glm::vec2(currentVertices[0]), axis);
    float proj2 = glm::dot(glm::vec2(currentVertices[1]), axis);
    float proj3 = glm::dot(glm::vec2(currentVertices[2]), axis);
    float proj4 = glm::dot(glm::vec2(currentVertices[3]), axis);
    return {std::min({proj1, proj2, proj3, proj4}), std::max({proj1, proj2, proj3, proj4})};
}


} // namespace RavenEngine