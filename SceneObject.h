#pragma once
#pragma once
#include "Model.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SceneObject
{
public:
    SceneObject(Model* model, Shader* shader);
   // void Draw() const;

    void SetPosition(const glm::vec3& pos);
    void SetRotation(const glm::vec3& eulerAngles); // in degrees
    void SetScale(const glm::vec3& scl);

    glm::vec3 GetPosition();

    glm::mat4 GetModelMatrix() const;
    Shader* GetShader()const;
    void Draw(Shader& shader) const;

    bool IsTransparent();
    void SetTransparent(bool tr);
     void DrawNode(Shader& shader, const Node* node, const glm::mat4& parentTransform);
     void DebugDrawSingleMesh(/*const Model* model,*/ Shader& shader, const glm::mat4& view, const glm::mat4& projection);
private:
    Model* model;
    Shader* shader;
    bool isTransparent;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    void DrawNode(Node* node, Shader& shader, glm::mat4 parentTransform) const;
    void printMat4(const glm::mat4& mat, const std::string msg);
};

