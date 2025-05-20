#include "DirectionalLight.h"

// Light.cpp

DirectionalLight::DirectionalLight(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& col)
    : position(pos), direction(dir), color(col)
{
}

void DirectionalLight::ApplyToShader(const Shader& shader) const {
    shader.use();
    shader.setVec3("u_lightPos", position);
    shader.setVec3("u_lightDir", direction);
    shader.setVec3("u_lightColor", color);
}

