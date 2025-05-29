#include "Camera.h"
#include <iostream>

 
Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 upVec)
    : position(pos), worldUp(upVec), yaw(-90.0f), pitch(0.0f), movementSpeed(12.5f), mouseSensitivity(0.1f)
{
    front = glm::normalize(target - position);
    updateCameraVectors();
}

//glm::mat4 Camera::GetViewMatrix() const {
//    return glm::lookAt(position, target, up);
//}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
}

glm::vec3 Camera::GetPosition() const {
    return position;
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);

    // Also re-calculate Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::ProcessKeyboardMovement(char direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    

    if (direction == 'W')
        position += front * velocity;
    if (direction == 'S')
        position -= front * velocity;
    if (direction == 'A')
        position -= right * velocity;
    if (direction == 'D')
        position += right * velocity;

    //  std::cout <<  "position " << position.x << "GETposition" << GetPosition(.x << std::endl;
   // std::cout << "position z" << position.z << std::endl;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Constrain the pitch so screen doesn't flip
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}