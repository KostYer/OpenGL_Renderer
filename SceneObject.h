#pragma once
#pragma once
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SceneObject
{
public:
    SceneObject(Model* model, Shader* shader);
    void Draw() const;

    void SetPosition(const glm::vec3& pos);
    void SetRotation(const glm::vec3& eulerAngles); // in degrees
    void SetScale(const glm::vec3& scl);

    glm::mat4 GetModelMatrix() const;
    Shader* GetShader()const;
    void Draw(Shader& shader) const;

private:
    Model* model;
    Shader* shader;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

