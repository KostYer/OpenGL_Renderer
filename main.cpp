#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <glad/gl.h>
#include <glm/glm.hpp>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include "Application.h"

SDL_Window* gGraphicApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;
//1920x1080
int gScreenHeight = 1920;
int gScreenWidht = 1080;
SDL_Window* window;
bool isActive = true;


#include <iostream>
#include "Renderer.h"



int main() {
    Application app;

    Renderer renderer(gScreenWidht, gScreenWidht);

    if (!renderer.Init()) 
    {
        std::cerr << "Failed to initialize renderer.\n";
        return -1;
    }

    renderer.LoadScene();
 
    //while (!app.ShouldCloseWindow()) {
    while (true) {
        // Calculate delta time
        static auto lastFrameTime = std::chrono::high_resolution_clock::now();
        auto currentFrameTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentFrameTime - lastFrameTime).count();
        lastFrameTime = currentFrameTime;

        // Handle input
        app.PollInput(deltaTime, renderer.camera);
        renderer.RenderFrame();
        // Update scene, render objects, etc.
      //  app.RenderFrame();

    }

    

   // renderer.RunMainLoop();

   // renderer.Cleanup();

    return 0;
}
  