#include "Application.h"
 
 
Application::Application()
{
    lastFrameTime = std::chrono::high_resolution_clock::now();

}

    void Application::Run() {
        while (!ShouldCloseWindow()) {
            float deltaTime = CalculateDeltaTime();

         //   PollInput(deltaTime);
            Update(deltaTime);
            Render();
        }
    }

    
    std::chrono::high_resolution_clock::time_point lastFrameTime;

    float Application::CalculateDeltaTime() {
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> elapsed = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;
        return elapsed.count();
    }


    void Application::Update(float deltaTime) {
        // Any per-frame updates (animations, physics, etc) here.
    }

    void Application::Render() {
      ///  glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                (float)screenWidth / screenHeight,
                                                0.1f, 100.0f);

    }

    // Placeholder functions to replace with your input library:
    bool Application::IsKeyPressed(char key) {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        switch (key) {
        case 'W': return state[SDL_SCANCODE_W];
        case 'A': return state[SDL_SCANCODE_A];
        case 'S': return state[SDL_SCANCODE_S];
        case 'D': return state[SDL_SCANCODE_D];
        default: return false;
        }
    }

    float Application::GetMouseDeltaX() {
        int x, y;
        SDL_GetRelativeMouseState(&x, &y); // relative movement since last call
        return static_cast<float>(x);
    }

    float Application::GetMouseDeltaY() {
        int x, y;
        SDL_GetRelativeMouseState(&x, &y);
        return static_cast<float>(y);
    }

    bool Application::ShouldCloseWindow() {
        return quit;
    }

    void Application::PollInput(float deltaTime, Camera& camera, SDL_Window* window) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                SDL_SetRelativeMouseMode(SDL_FALSE);
                SDL_SetWindowGrab(window, SDL_FALSE);
            }
 
        }

        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_W]) camera.ProcessKeyboardMovement('W', deltaTime);
        if (state[SDL_SCANCODE_S]) camera.ProcessKeyboardMovement('S', deltaTime);
        if (state[SDL_SCANCODE_A]) camera.ProcessKeyboardMovement('A', deltaTime);
        if (state[SDL_SCANCODE_D]) camera.ProcessKeyboardMovement('D', deltaTime);

        int mouseX, mouseY;
        SDL_GetRelativeMouseState(&mouseX, &mouseY);

        float sensitivity = 0.7f;
        camera.ProcessMouseMovement(mouseX * sensitivity, -mouseY * sensitivity);
    }

    int screenWidth = 800;
    int screenHeight = 600;

    // Your shader and scene objects...
    Shader* shader;
    std::vector<SceneObject*> sceneObjects;
 
