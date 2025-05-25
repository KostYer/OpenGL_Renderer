#pragma once
#include <string>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "Node.h"

class Node; // Forward declaration
class Mesh;

class Model
{
   
public:
    Model(const std::string& path);
    Model();

    void Draw(const Shader& shader) const; // Pass shader by const reference
    Node* rootNode;
    std::vector<Mesh*> meshes;
private:
   
 
    Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

