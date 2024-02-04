// Camera.h
#pragma once

#include <glm/glm.hpp>

namespace RavenEngine {

class Camera {
public:
    Camera(float left, float rightBound, float bottom, float top, float nearPlane, float farPlane);

    // Getters
    const glm::mat4& GetViewMatrix() const;
    const glm::mat4& GetProjectionMatrix() const;

    // Camera transformations
    void Move(const glm::vec3& offset);
    void Rotate(float yaw, float pitch);

    // Update the camera
    void Update();

    // Set projection
    void setProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 rightVector; // Renamed to avoid conflict
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;
    float zoom;

    // Projection properties
    float left;
    float rightBound; // Renamed to avoid conflict
    float bottom;
    float top;
    float nearPlane;
    float farPlane;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    void updateCameraVectors();
    void updateViewMatrix();
    void updateProjectionMatrix();
};

} // namespace RavenEngine