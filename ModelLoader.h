#pragma once
#include "Model.h"

class ModelLoader {
public:
    static Model* LoadFromFile(const std::string& path);

private:
    static Node* ProcessNode(aiNode* ainode, const aiScene* scene, Model* model);
    static Mesh* ProcessMesh(aiMesh* aimesh, const aiScene* scene);
};
