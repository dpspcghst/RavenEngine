// triangle.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third party includes
#include <glm/gtc/type_ptr.hpp> // Include the glm/gtc/type_ptr.hpp library to use glm::value_ptr

// Local project includes
#include "../../Shaders/ShaderManager.h"
#include "Triangle.h"

namespace RavenEngine {

Triangle::Triangle() : Shape2D() {
    type = Type::Triangle;
    vertices[0] = glm::vec3(0.0f, -0.5f, 0.0f);
    vertices[1] = glm::vec3(-0.5f, 0.5f, 0.0f);
    vertices[2] = glm::vec3(0.5f, 0.5f, 0.0f);
    color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // Red color for the triangle by default
}

Triangle::~Triangle() {
    // Cleanup handled by Shape2D destructor
}

void Triangle::Create() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);
}

void Triangle::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<RavenEngine::ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());

    if (shaderProgramPtr) {
        GLuint shaderProgramID = shaderProgramPtr->GetID();
        glUseProgram(shaderProgramID);

        // Set the shader uniforms
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "model"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, GetVertexCount());
        glBindVertexArray(0);
    } else {
        std::cerr << "Triangle::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}


int Triangle::GetVertexCount() const {
    return 3; // Number of vertices in a triangle
}

} // namespace RavenEngine