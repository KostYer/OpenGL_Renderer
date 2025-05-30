#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 target, glm::vec3 up);


    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

    glm::vec3 GetPosition() const;
    void ProcessKeyboardMovement(char direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset);
    // Future movement methods can be added here:
    // void MoveForward(float delta);
    // void Rotate(float yaw, float pitch);
    glm::vec3 position;
private:
    glm::vec3 target;


   
    glm::vec3 front;   // Direction camera faces
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;   // Horizontal rotation angle (in degrees)
    float pitch; // Vertical rotation angle (in degrees)

    float movementSpeed;
    float mouseSensitivity;

    void updateCameraVectors();
};


 