#pragma once

#include <vector>
#include <string>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include "Shader.h"

class Skybox {
public:
     Skybox();
    ~Skybox();
    void Draw(const glm::mat4& view, const glm::mat4& projection);
  //  void setupSkyboxMesh();
  //  void loadCubemap(const std::vector<std::string>& faces);
    GLuint cubemapTexture;
private:
     void loadCubemap();

    GLuint skyboxVAO, skyboxVBO;
    
    Shader* skyboxShader;

    std::vector<std::string> faces = {
        "textures/skybox/right.png",
        "textures/skybox/left.png",
        "textures/skybox/top.png",
        "textures/skybox/bottom.png",
        "textures/skybox/front.png",
        "textures/skybox/back.png"
    };
};
