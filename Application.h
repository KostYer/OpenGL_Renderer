#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Shader.h"
#include <vector>
#include <chrono>
#include <SDL.h>

class Shader;
class SceneObject;

class Application {
public:
    Application();
    void Run();
    void PollInput(float deltaTime, Camera& camera);
    //Camera camera;
    bool ShouldCloseWindow();

private:
  //  void PollInput(float deltaTime);
    void Update(float deltaTime);
    void Render();
    float CalculateDeltaTime();
    bool IsKeyPressed(char key);
    float GetMouseDeltaX();
    float GetMouseDeltaY();
  //  bool ShouldCloseWindow();

private:
    Shader* shader;                        // Declared here
    std::vector<SceneObject*> sceneObjects;  // Declared here

    int screenWidth = 800;
    int screenHeight = 600;

    bool quit;

    // For timing
    std::chrono::high_resolution_clock::time_point lastFrameTime;

    
};
