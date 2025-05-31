#pragma once

#include <SDL.h>
#include "Shader.h"
#include "Model.h"
#include "DirectionalLight.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneObject.h"
#include "Skybox.h" 
#include "Camera.h"
#include "Node.h"
#include "ModelLoader.h"

class Renderer {
public:
    Renderer(int width, int height);
    ~Renderer();

    bool Init();
    void LoadScene();
    void RenderFrame();
    bool ShouldClose() const;
    ModelLoader modelLoader;
    Camera camera;
    SDL_Window* window = nullptr;
private:
   
    SDL_GLContext glContext;
    int screenWidth;
    int screenHeight;

    int SHADOW_WIDTH = 2048 *2;
    int SHADOW_HEIGHT = 2048 * 2;


    GLuint shadowFBO;
    GLuint shadowMap;
//    Camera camera;

    DirectionalLight DirectionalLight;
    Shader* shader = nullptr;
    Shader* shadowShader = nullptr;
    Model* model = nullptr;
    Skybox* skybox = nullptr;

    std::vector<SceneObject*> sceneObjects;

    glm::mat4 projection;
    glm::mat4 view;

    void RenderNode(Node* node, glm::mat4 parentTransform, Shader& shader);
    void InitShadows();
};