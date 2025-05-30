#include "Renderer.h"
#include <iostream>
#include "SceneObject.h"
#include "Camera.h"

Renderer::Renderer(int screenWidth, int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight),
    camera(glm::vec3(0.0f, 0.0f, 13.0f),     // position
        glm::vec3(0.0f, 0.0f, 0.0f),     // target
        glm::vec3(0.0f, 1.0f, 0.0f))     // up
{
    // Setup SDL, GLAD, OpenGL settings, etc.
}

Renderer::~Renderer() {
    delete shader;
    delete model;
    delete skybox;

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Renderer::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("OpenGL FBX Renderer",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        screenWidth, screenHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        return false;
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);

    skybox = new Skybox();

    // In Renderer::Init() or Application constructor:
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetWindowGrab(window, SDL_TRUE);

    return true;
}

void Renderer::LoadScene() {
     shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
 
      model = modelLoader.LoadFromFile("models/Floating_Island.fbx"); 
      glm::mat4 modelMatrix = glm::mat4(1); 
      modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0, 0, 1)); // rotate 45 degrees around Y
     // etc.
     shader->setMat4("model", &modelMatrix[0][0]);

     SceneObject* obj1 = new SceneObject(model, shader);
     obj1->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
      sceneObjects.push_back(obj1);
      ///Floating Island

   
  //  SceneObject* obj2 = new SceneObject(model, shader);
  //  obj2->SetPosition(glm::vec3(1.0f, 0.3f, 0.4f));
 //    sceneObjects.push_back(obj2);

  //   SceneObject* obj3 = new SceneObject(model, shader);
  //   obj3->SetPosition(glm::vec3(-0.3f, 0.9f, -6.0f));
  //   obj3->SetTransparent(true);
   // sceneObjects.push_back(obj3);

    projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);
    view = glm::lookAt(camera.GetPosition(),  // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // Look at origin
        glm::vec3(0.0f, 1.0f, 0.0f)); // Up vector
}
 
void Renderer::RenderFrame() {
 
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            exit(0);
    }

    view = camera.GetViewMatrix();


    glDisable(GL_CULL_FACE); //4debug
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw skybox first
    skybox->Draw(view, projection);

  

    // Separate opaque and transparent objects
    std::vector<SceneObject*> opaqueObjects;
    std::vector<SceneObject*> transparentObjects;

    for (SceneObject* obj : sceneObjects) {
        if (obj->IsTransparent()) {
            transparentObjects.push_back(obj);
        }
        else {
            opaqueObjects.push_back(obj);
        }
    }
   

    // Draw opaque objects
    for (SceneObject* obj : opaqueObjects) {
        Shader* currentShader = obj->GetShader();
         currentShader->use(); ///plug in rend pipeline

         ///reflections
        // Bind cubemap texture for reflections
         glActiveTexture(GL_TEXTURE0 + 5);
         glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->cubemapTexture);
         
         currentShader->setInt("u_skybox", 5);
         currentShader->setVec3("u_viewPos", camera.position);



         ///reflections end

        // obj->SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));

        currentShader->setMat4("projection", &projection[0][0]);
        currentShader->setMat4("view", &view[0][0]);
         DirectionalLight.ApplyToShader(*currentShader);

        obj->Draw(*currentShader);
       // obj->DebugDrawSingleMesh( *currentShader, view, projection);
    }

    // Enable blending and disable depth write
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    // Sort transparent objects back-to-front
    std::sort(transparentObjects.begin(), transparentObjects.end(),
        [&](SceneObject* a, SceneObject* b) {
            float distA = glm::length(camera.GetPosition() - a->GetPosition());
            float distB = glm::length(camera.GetPosition() - b->GetPosition());
            return distA > distB; // Farther objects drawn first
        });

    // Draw transparent objects
    for (SceneObject* obj : transparentObjects) {
        Shader* currentShader = obj->GetShader();
        currentShader->use();

        currentShader->setMat4("projection", &projection[0][0]);
        currentShader->setMat4("view", &view[0][0]);
        DirectionalLight.ApplyToShader(*currentShader);

        obj->Draw(*currentShader);
    }

    // Restore state
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    SDL_GL_SwapWindow(window);
 
}

bool Renderer::ShouldClose() const {
    return false; // Modify if adding input/exit logic
}

void Renderer::RenderNode(Node* node, glm::mat4 parentTransform, Shader& shader) {
    glm::mat4 globalTransform = parentTransform * node->localTransform;

    // Draw each mesh with global transform
    for (Mesh* mesh : node->meshes) {
        shader.setMat4("model", &globalTransform[0][0]);
        mesh->Draw(shader);
    }

    // Recursively draw children
    for (Node* child : node->children) {
        RenderNode(child, globalTransform, shader);
    }
}