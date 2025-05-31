#include "Model.h"
#include "Mesh.h"
#include "Shader.h"

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#include <iostream>

 

Model::Model(const std::string& path)
{
}

Model::Model() {
    // Initialize rootNode to nullptr (already done in-class if using C++11+)
    rootNode = nullptr;
}

void Model::Draw(const Shader& shader) const {
    for (const auto& mesh : meshes) {
        mesh->Draw(shader);
    }
}

 