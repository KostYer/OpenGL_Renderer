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

        // Vertex Color
        if (mesh->HasVertexColors(0)) {
            aiColor4D c = mesh->mColors[0][i];
               vertex.Color = glm::vec4(c.r, c.g, c.b, c.a);
          //  vertex.Color = glm::vec4(1, 0, 0, 1);
        }
        else {
         //   vertex.Color = glm::vec4(1.0f); // fallback white
            vertex.Color = glm::vec4(0, 1, 0, 1);
           //  std::cout << "Has NO VertexColors "   << std::endl;
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


  /*  for (int i = 0; i < std::min(10, (int)mesh->mNumVertices); ++i) {
        aiColor4D c = mesh->mColors[0][i];
        std::cout << "Vertex " << i << " Color: "
            << c.r << ", " << c.g << ", " << c.b << ", " << c.a << std::endl;
    }*/

    // Create the Mesh on the heap and return a pointer to it
    return new Mesh(vertices, indices);
}