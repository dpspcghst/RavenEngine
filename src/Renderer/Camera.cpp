// Camera.cpp
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace RavenEngine {

Camera::Camera(float fov, float aspectRatio, float nearPlane, float farPlane)
    : position(glm::vec3(0.0f, 0.0f, 0.0f)),
      worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
      yaw(-90.0f), pitch(0.0f),
      movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f),
      fov(fov), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane) {
    updateCameraVectors();
    updateViewMatrix();
    updateProjectionMatrix();
}

const glm::mat4& Camera::GetViewMatrix() const {
    return viewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::Move(const glm::vec3& offset) {
    position += offset;
}

void Camera::Rotate(float yawOffset, float pitchOffset) {
    yaw += yawOffset;
    pitch += pitchOffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::Update() {
    updateViewMatrix();
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, front));
}

void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, position + front, up);
}

void Camera::updateProjectionMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

} // namespace RavenEngine