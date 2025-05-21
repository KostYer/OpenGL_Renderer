#include "Renderer.h"
#include <iostream>
#include "SceneObject.h"

Renderer::Renderer(int width, int height)
    : screenWidth(width), screenHeight(height) {
}

Renderer::~Renderer() {
    delete shader;
    delete model;

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

    return true;
}

void Renderer::LoadScene() {
     shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
     model = new Model("models/Sphere1.fbx");
    
     glm::mat4 modelMatrix = glm::translate(glm::mat4(1), glm::vec3(-112.0f, 0.0f, 0.0f)); // your SceneObject::GetModelMatrix()
     // etc.
     shader->setMat4("model", &modelMatrix[0][0]);


     SceneObject* obj1 = new SceneObject(model, shader);
     obj1->SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
      sceneObjects.push_back(obj1);


   // SceneObject* obj2 = new SceneObject(model, shader);
  //  obj2->SetPosition(glm::vec3(-2.2f, 0.3f, 0.4f));
  //  sceneObjects.push_back(obj2);

    projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / screenHeight, 0.1f, 100.0f);
    view = glm::lookAt(glm::vec3(0.0f, 1.0f, 6.0f),  // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f),  // Look at origin
        glm::vec3(0.0f, 1.0f, 0.0f)); // Up vector
}

void Renderer::RenderFrame() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            exit(0);
    }

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (SceneObject* obj : sceneObjects) {
        Shader* currentShader = obj->GetShader();
        currentShader->use();

        currentShader->setMat4("projection", &projection[0][0]);
        currentShader->setMat4("view", &view[0][0]);

        DirectionalLight.ApplyToShader(*currentShader);
        obj->Draw(*currentShader);
    }

    SDL_GL_SwapWindow(window);
}

bool Renderer::ShouldClose() const {
    return false; // Modify if adding input/exit logic
}