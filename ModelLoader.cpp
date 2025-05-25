#include "ModelLoader.h"
#include "Mesh.h"
#include <vector>
#include "Node.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Utility to convert aiMatrix4x4 to glm::mat4
static glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from) {
    return glm::mat4(
        from.a1, from.b1, from.c1, from.d1,
        from.a2, from.b2, from.c2, from.d2,
        from.a3, from.b3, from.c3, from.d3,
        from.a4, from.b4, from.c4, from.d4
    );
}

// -- Mesh --

Mesh* ModelLoader::ProcessMesh(aiMesh* aimesh, const aiScene* scene) {

    std::cout << "Processing mesh with " << aimesh->mNumVertices << " vertices and "
        << aimesh->mNumFaces << " faces." << std::endl;

    Mesh* mesh = new Mesh();

    // Extract vertex data (positions, normals, uvs)
    for (unsigned int i = 0; i < aimesh->mNumVertices; i++) {
        Vertex vertex;

        // Position
        vertex.Position = glm::vec3(
            aimesh->mVertices[i].x,
            aimesh->mVertices[i].y,
            aimesh->mVertices[i].z);

        // Normal (check if exists)
        if (aimesh->HasNormals()) {
            vertex.Normal = glm::vec3(
                aimesh->mNormals[i].x,
                aimesh->mNormals[i].y,
                aimesh->mNormals[i].z);
        }
        else {
            vertex.Normal = glm::vec3(0.0f);
        }

        // Texture coordinates (check if exists)
        if (aimesh->mTextureCoords[0]) {
            vertex.TexCoords = glm::vec2(
                aimesh->mTextureCoords[0][i].x,
                aimesh->mTextureCoords[0][i].y);
        }
        else {
            vertex.TexCoords = glm::vec2(0.0f);
        }

        mesh->vertices.push_back(vertex);
    }

    // Extract indices
    for (unsigned int i = 0; i < aimesh->mNumFaces; i++) {
        aiFace face = aimesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            mesh->indices.push_back(face.mIndices[j]);
        }
    }

    std::cout << "Extracted mesh with " << mesh->vertices.size() << " vertices and "
        << mesh->indices.size() << " indices." << std::endl;
    mesh->setupMesh();  // <-- Add this call here!
    return mesh;
}

// -- Node --

Node* ModelLoader::ProcessNode(aiNode* ainode, const aiScene* scene, Model* model) {

    std::cout << "Processing node: " << ainode->mName.C_Str()
        << ", meshes: " << ainode->mNumMeshes
        << ", children: " << ainode->mNumChildren << std::endl;


    std::cout << "ProcessNode "<< std::endl;
    Node* node = new Node();
    node->localTransform = aiMatrix4x4ToGlm(ainode->mTransformation);
    std::cout << "Number of meshes: " << ainode->mNumMeshes << std::endl;
    for (unsigned int i = 0; i < ainode->mNumMeshes; i++) {
        aiMesh* aimesh = scene->mMeshes[ainode->mMeshes[i]];
        Mesh* mesh = ProcessMesh(aimesh, scene);
        node->meshes.push_back(mesh);
        model->meshes.push_back(mesh); // if your Model::meshes is std::vector<Mesh>, push by value
        // or model->meshes.push_back(mesh); if Model::meshes is vector<Mesh*>
    }

    for (unsigned int i = 0; i < ainode->mNumChildren; i++) {
        node->children.push_back(ProcessNode(ainode->mChildren[i], scene, model));
    }
    return node;
}

// -- ModelLoader --

Model* ModelLoader::LoadFromFile(const std::string& path) {
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path,
        aiProcess_Triangulate |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs |
        aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return nullptr;
    }

    Model* model = new Model();
    model->rootNode = ProcessNode(scene->mRootNode, scene, model);
   // std::cout << "Number of indices in first mesh: " << model->meshes[0]->indices.size() << std::endl;
    std::cout << "Model loaded with " << model->meshes.size() << " meshes." << std::endl;

    if (!model->meshes.empty()) {
        std::cout << "First mesh indices count: " << model->meshes[0]->indices.size() << std::endl;
        std::cout << "First mesh vertices count: " << model->meshes[0]->vertices.size() << std::endl;
    }
    else {
        std::cout << "Model contains no meshes!" << std::endl;
    }
    return model;
}

// -- Destructors to free memory --

 
