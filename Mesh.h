#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>
#include "Vertex.h"
#include "Shader.h"


class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    void Draw(const Shader& shader) const;

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

