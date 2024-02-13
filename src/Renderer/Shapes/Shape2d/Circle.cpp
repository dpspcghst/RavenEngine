// Circle.cpp

// #include section
// #####################
// Standard library includes
#include <iostream>

// Third-party includes
#include <glm/gtc/type_ptr.hpp>

// Raven includes
#include "Circle.h"
#include "../../Shaders/ShaderManager.h"
#include "../../Texture/TextureManager.h"

namespace RavenEngine {

Circle::Circle() {
    // Initialize your Circle object here
}

Circle::Circle(float radius, int segments) 
    : Shape2D(), radius(radius), segments(segments), textureId(0) {
    // Initialize the circle's color to white by default
    color = glm::vec4(1.0f); 
}

Circle::~Circle() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Circle::Create() {
    std::vector<GLfloat> vertices;
    const GLfloat PI = 3.14159265359f;
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * PI * float(i) / float(segments);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(0.0f); // Z coordinate is zero for 2D shapes
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0); 
}

void Circle::Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
    ShaderManager& shaderManager = ShaderManager::GetInstance();
    std::shared_ptr<ShaderProgram> shaderProgramPtr = shaderManager.GetShader(GetShaderName());
    
    if (shaderProgramPtr) {
        shaderProgramPtr->Use();
        
        // Set shader uniforms
        glUniformMatrix4fv(shaderProgramPtr->GetUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(GetTransformMatrix()));
        glUniformMatrix4fv(shaderProgramPtr->GetUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(shaderProgramPtr->GetUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // Bind texture if available
        TextureInfo textureInfo = TextureManager::GetInstance().GetTexture(GetTextureId());
        if (textureInfo.id != 0) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureInfo.id);
            shaderProgramPtr->SetUniform("u_Texture", 0);
        }

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, segments + 2);
        glBindVertexArray(0);
    } else {
        std::cerr << "Circle::Render: Failed to retrieve shader program for '" << GetShaderName() << "'." << std::endl;
    }
}

int Circle::GetVertexCount() const {
    return segments + 2; // +2 for the center and the closing vertex
}

} // namespace RavenEngine
