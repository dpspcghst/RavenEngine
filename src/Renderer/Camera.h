// Camera.h
#pragma once

#include <glm/glm.hpp>

namespace RavenEngine {

class Camera {
public:
    Camera(float fov, float aspectRatio, float nearPlane, float farPlane);

    // Getters
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;

    // Camera transformations
    void Move(const glm::vec3& offset);
    void Rotate(float yaw, float pitch); // yaw = rotation around y-axis, pitch = rotation around x-axis

    // Update the camera (call this every frame)
    void Update();

private:
    // Camera properties
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // Eular Angles
    float yaw;
    float pitch;

    // Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    // Projection properties
    float fov; // field of view
    float aspectRatio;
    float nearPlane;
    float farPlane;

    // Matrices
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    // Private methods
    void updateCameraVectors();
    void updateViewMatrix();
    void updateProjectionMatrix();
};

} // namespace RavenEngine