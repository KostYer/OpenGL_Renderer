#include "SceneObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <iomanip>

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
 


void SceneObject::Draw(Shader& shader) const {
   
    if (!model || !model->rootNode)
        return;

    glm::mat4 rootTransform = GetModelMatrix();  // SceneObject's transform
    DrawNode(model->rootNode, shader, rootTransform);
}
 

void SceneObject::DrawNode(Node* node, Shader& shader, glm::mat4 parentTransform) const {
    glm::mat4 currentTransform = parentTransform * node->localTransform;

    for (Mesh* mesh : node->meshes) {
        shader.setMat4("model", &currentTransform[0][0]);
        mesh->Draw(shader);
    }

    for (Node* child : node->children) {
        DrawNode(child, shader, currentTransform);
    }
}

bool SceneObject::IsTransparent()
{
    return isTransparent;
}
void SceneObject::SetTransparent(bool tr)
{
    isTransparent = tr;
}



void SceneObject::DebugDrawSingleMesh(/*const Model* model,*/ Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
    shader.use();
    shader.setMat4("view", &view[0][0]);
    shader.setMat4("projection", &projection[0][0]);

    // Safety checks
    if (!model || !model->rootNode || model->rootNode->children.empty()) {
        std::cout << "Model has no children!" << std::endl;
        return;
    }
    

    Node* child = model->rootNode->children[20];  // First child node

    if (child->meshes.empty()) {
        std::cout << "Child node has no meshes!" << std::endl;
        return;
    }

    Mesh* mesh = child->meshes[0];  // First mesh of the first child

 //   glm::mat4 modelMatrix = child->localTransform;
    glm::mat4 modelMatrix = glm::mat4(1);

     glm::mat4 manualTransform = model->rootNode->localTransform * child->localTransform;
     shader.setMat4("model", &manualTransform[0][0]);
 
    
    mesh->Draw(shader);
  //  std::cout << "Drawing mesh at address: " << mesh << ", VAO: " << mesh->VAO << std::endl;
}
void SceneObject::printMat4(const glm::mat4& mat, const std::string msg) {

    std::cout << msg << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << std::fixed << std::setprecision(4) << std::setw(10) << mat[j][i] << " ";
        }
        std::cout << std::endl;
    }
}
  
