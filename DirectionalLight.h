// Light.h
#pragma once
#include <glm/glm.hpp>
#include "Shader.h"  // Your shader class

class DirectionalLight {
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;

    DirectionalLight(
        const glm::vec3& pos = glm::vec3(0.0f, -100.0f, 0.0f),
        const glm::vec3& dir = glm::vec3(1.0f, 1.0f, 1.0f),
        const glm::vec3& col = glm::vec3(1.0f)
    );

    // Pass light uniforms to a shader
    void ApplyToShader(const Shader& shader) const;
};
 