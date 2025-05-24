#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    glm::vec3 GetPosition() const;

    // Future movement methods can be added here:
    // void MoveForward(float delta);
    // void Rotate(float yaw, float pitch);

private:
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 up;
};