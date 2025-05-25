#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <glad/gl.h>
#include <glm/glm.hpp>

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
 

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
    Renderer renderer(gScreenWidht, gScreenWidht);

    if (!renderer.Init()) 
    {
        std::cerr << "Failed to initialize renderer.\n";
        return -1;
    }

    renderer.LoadScene();

    while (true)
    {
        renderer.RenderFrame();
    }

   // renderer.RunMainLoop();

   // renderer.Cleanup();

    return 0;
}

//
//
//bool InitializeProgram()
//{
//    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
//        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
//        return false;
//    }
//
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//
//    window = SDL_CreateWindow(
//        "SDL2 + GLAD OpenGL",
//        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//        gScreenWidht, gScreenHeight,
//        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
//    );
//
//    if (!window) {
//        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
//        SDL_Quit();
//        return false;
//    }
//
//    gOpenGLContext = SDL_GL_CreateContext(window);
//    if (!gOpenGLContext) {
//        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << "\n";
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return false;
//    }
//
//    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
//        std::cerr << "Failed to initialize GLAD\n";
//        SDL_GL_DeleteContext(gOpenGLContext);
//        SDL_DestroyWindow(window);
//        SDL_Quit();
//        return false;
//    }
//
//    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
//    return true;
//
//}
//
//void PreDraw()
//{
//    glViewport(0, 0, gScreenWidht, gScreenHeight);
//    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//}
//
//void Draw()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    SDL_GL_SwapWindow(window);
//}
//
//void CleanUp() {
//    SDL_GL_DeleteContext(gOpenGLContext);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//}
//
//
//void MainLoop()
//{
//
//    bool running = true;
//    SDL_Event event;
//
//    while (running) {
//        while (SDL_PollEvent(&event)) {
//            if (event.type == SDL_QUIT) {
//                running = false;
//            }
//        }
//
//        PreDraw();
//        Draw();
//    }
//
//    CleanUp();
//}
//
//
//int main()
//{ 
//    if(!InitializeProgram())
//    {
//        return -1;
//    }
//    MainLoop();
//    return 0;
//}
//
// 