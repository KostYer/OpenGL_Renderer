#include "Model.h"
#include "Mesh.h"
#include "Shader.h"

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

#include <iostream>

 

Model::Model(const std::string& path) {
    LoadModel(path);
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

void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;

    // Flags for post-processing
    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |          // convert all polygons to triangles
        aiProcess_FlipUVs |              // flip UV coordinates (optional)
        aiProcess_CalcTangentSpace |    // calculate tangent space (optional)
        aiProcess_GenNormals |           // generate normals if missing
        aiProcess_JoinIdenticalVertices // join duplicate vertices
    );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
    // Process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    // Then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Process vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // Positions
        vertex.Position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        // Normals
        if (mesh->HasNormals()) {
            vertex.Normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        }
        else {
            vertex.Normal = glm::vec3(0.0f, 0.0f, 0.0f);
        }

        // Texture Coordinates (only support 1 set for now)
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Create the Mesh on the heap and return a pointer to it
    return new Mesh(vertices, indices);
}