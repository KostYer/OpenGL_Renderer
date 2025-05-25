#pragma once
#include <glm/glm.hpp>
#include "Model.h"
//#include "Mesh.h"
class Mesh; // 👈 forward declaration


struct Node {
    glm::mat4 localTransform;
    std::vector<Mesh*> meshes;
    std::vector<Node*> children;
};