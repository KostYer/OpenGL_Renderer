#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up)
    : position(position), target(target), up(up) {
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, target, up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

glm::vec3 Camera::GetPosition() const {
    return position;
}