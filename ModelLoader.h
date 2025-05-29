#pragma once
#include "Model.h"

class ModelLoader {
public:
    static Model* LoadFromFile(const std::string& path);

private:
    static Node* ProcessNode(aiNode* ainode, const aiScene* scene, Model* model, const glm::mat4& parentTransform);
    static Mesh* ProcessMesh(aiMesh* aimesh, const aiScene* scene);
};
