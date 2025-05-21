#pragma once

#include <SDL.h>
#include "Shader.h"
#include "Model.h"
#include "DirectionalLight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneObject.h"
#include "Skybox.h"    

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    bool Init();
    void LoadScene();
    void RenderFrame();
    bool ShouldClose() const;

private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext;
    int screenWidth;
    int screenHeight;

    DirectionalLight DirectionalLight;
    Shader* shader = nullptr;
    Model* model = nullptr;
    Skybox* skybox = nullptr;

    std::vector<SceneObject*> sceneObjects;

    glm::mat4 projection;
    glm::mat4 view;
};