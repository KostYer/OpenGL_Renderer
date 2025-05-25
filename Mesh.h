#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include "Shader.h"
#include "Node.h"

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    Mesh();
    Node* rootNode;

    void Draw(const Shader& shader) const;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    void setupMesh();
private:
   

    unsigned int VAO, VBO, EBO;

   
};

