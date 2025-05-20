#pragma once
#include <string>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Mesh.h"

class Model
{
   
public:
    Model(const std::string& path);
  //  bool LoadFromFile(const std::string& path);
    //void Draw() const;
    void Draw(const Shader& shader) const;  // Pass shader by const reference

private:
    std::vector<Mesh> meshes;
   // void ProcessMesh(const aiMesh* mesh);
    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

