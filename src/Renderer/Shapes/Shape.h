// shape.h
#pragma once

// #include section
// #####################
// Standard library includes
#include <string>
// Third party includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// Raven includes
#include "../Shaders/ShaderManager.h"
#include "../Materials/MaterialProperties.h"
#include "../Materials/MaterialProperties3D.h"

namespace RavenEngine {
class Shape {
public:
    static int nextID;

    enum class ShapeType {                                                                          // Enum class for shape type (2D or 3D)
        Shape2D,
        Shape3D,
    };
    virtual ShapeType GetType() const = 0;

    Shape() : shaderName(""), shaderProgram(0), ID(0), materialUBOName(""), color(glm::vec4(1.0f)), // Default constructor
              size(glm::vec3(1.0f)), position(glm::vec3(0.0f)), rotation(glm::vec3(0.0f)), 
              VAO(0), VBO(0), ubo(0), bindingPoint(0), transformMatrix(glm::mat4(1.0f)) {
        // Initialize other members as needed.
    }

    Shape(const std::string& shaderName) : Shape() {                                                // Constructor that accepts a shader name
        SetShaderName(shaderName);
    }

    virtual ~Shape() = default;                                                                     // Destructor

    // Create and render methods
    virtual void Create() = 0; // Create the shape
    virtual void Render(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const = 0;  // Render the shape

    virtual glm::mat4 GetTransformMatrix() const = 0; // Get the transform matrix
    virtual void UpdateTransformMatrix() { // Update the transform matrix
        transformMatrix = glm::mat4(1.0f);
        transformMatrix = glm::translate(transformMatrix, position);
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
        transformMatrix = glm::rotate(transformMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
        transformMatrix = glm::scale(transformMatrix, size);
    }

    // Setters and getters
    virtual void SetID(int id); // Set the ID
    virtual int GetID() const;  // Get the ID
    

    virtual void SetShaderName(const std::string& shaderName); // Set the shader name
    virtual const std::string& GetShaderName() const; // Get the shader name
    GLuint GetShaderProgram() const { return shaderProgram; } // Get the shader program

    virtual void SetMaterialUBOName(const std::string& name); // Set the material UBO name
    virtual std::string GetMaterialUBOName() const; // Get the material UBO name

    void SetTextureId(int id); // Set the texture ID
    int GetTextureId() const; // Get the texture ID

    virtual void SetSize(const glm::vec3& newSize); // Set the size
    virtual glm::vec3 GetSize() const; // Get the size

    virtual void SetPosition(const glm::vec3& newPosition); // Set the position
    virtual glm::vec3 GetPosition() const; // Get the position

    virtual void SetRotation(const glm::vec3& newRotation); // Set the rotation
    virtual glm::vec3 GetRotation() const; // Get the rotation

    // 2d shader
    virtual void SetColor(const glm::vec4& newColor); // Set the color
    virtual glm::vec4 GetColor() const; // Get the color

    // 3d shader
    virtual void SetShininess(float newShininess); // Set the shininess
    virtual float GetShininess() const; // Get the shininess

    virtual void SetAmbient(const glm::vec3& newAmbient); // Set the ambient
    virtual glm::vec3 GetAmbient() const; // Get the ambient

    virtual void SetDiffuse(const glm::vec3& newDiffuse); // Set the diffuse
    virtual glm::vec3 GetDiffuse() const; // Get the diffuse

    virtual void SetSpecular(const glm::vec3& newSpecular); // Set the specular
    virtual glm::vec3 GetSpecular() const;

protected:
    int textureId;
    int ID;
    std::string shaderName;
    GLuint shaderProgram;
    
    std::string materialUBOName;
    GLuint bindingPoint;
    GLuint VAO, VBO, ubo;
    
    glm::mat4 transformMatrix;
    glm::vec3 size;
    glm::vec3 position;
    glm::vec3 rotation;

    // 2d shader
    glm::vec4 color;

    // 3d shader
    float shininess;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

} // namespace RavenEngine