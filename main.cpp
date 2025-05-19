#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <glad/gl.h>
#include <glm/glm.hpp>
 

SDL_Window* gGraphicApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

int gScreenHeight = 600;
int gScreenWidht = 800;
SDL_Window* window;
bool isActive = true;



bool InitializeProgram()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(
        "SDL2 + GLAD OpenGL",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        gScreenWidht, gScreenHeight,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    gOpenGLContext = SDL_GL_CreateContext(window);
    if (!gOpenGLContext) {
        std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        SDL_GL_DeleteContext(gOpenGLContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
    return true;

}

void PreDraw()
{
    glViewport(0, 0, gScreenWidht, gScreenHeight);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

void CleanUp() {
    SDL_GL_DeleteContext(gOpenGLContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void MainLoop()
{

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        PreDraw();
        Draw();
    }

    CleanUp();
}


int main()
{ 
    InitializeProgram();
   
    MainLoop();
    return 0;
}

 