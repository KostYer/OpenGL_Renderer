#include "SceneObject.h"
#include <glm/gtc/matrix_transform.hpp>

SceneObject::SceneObject(Model* model, Shader* shader)
    : model(model), shader(shader),
    position(0.0f), rotation(0.0f), scale(1.0f) {
}

void SceneObject::SetPosition(const glm::vec3& pos) {
    position = pos;
}

void SceneObject::SetRotation(const glm::vec3& eulerAngles) {
    rotation = eulerAngles;
}

void SceneObject::SetScale(const glm::vec3& scl) {
    scale = scl;
}

glm::vec3 SceneObject::GetPosition()
{
    return position;
}

glm::mat4 SceneObject::GetModelMatrix() const {
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, position);
    mat = glm::rotate(mat, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    mat = glm::rotate(mat, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    mat = glm::rotate(mat, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    mat = glm::scale(mat, scale);
    return mat;
}

Shader* SceneObject::GetShader()const
{
    return shader;
}

void SceneObject::Draw() const {
    shader->use();
    shader->setMat4("model", &GetModelMatrix()[0][0]);
    model->Draw(*shader);
}

void SceneObject::Draw(Shader& shader) const {
    shader.setMat4("model", &GetModelMatrix()[0][0]);
    model->Draw(shader);
}

bool SceneObject::IsTransparent()
{
    return isTransparent;
}
void SceneObject::SetTransparent(bool tr)
{
    isTransparent = tr;
}