#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "DebugGameObject.h"
#include "InputSystem.h"
#include "GameObjectSystem.h"
#include "MemoryModule.h"
#include "BackgroundGameObject.h"
#include "Engine.h"

static GLFWwindow* window;
//static Engine engine;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

void initWindow()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(900, 900, "LearnOpenGL", NULL, NULL);

  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }

  glViewport(0, 0, 900, 900);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

int main()
{
  initWindow();

  Engine* engine = Engine::instance();
    
  //engine->AddSystem(new MemoryModule(100));
  engine->AddSystem(new InputSystem(window));
  engine->AddSystem(new GameObjectSystem());

  engine->EngineLoad();

  GameObjectSystem* goS = engine->GetSystem<GameObjectSystem>();
  goS->AddGameObject(new BackgroundGameObject()); 
  goS->AddGameObject(new DebugGameObject());

  float dt = 0.01667f;
  while (!glfwWindowShouldClose(window))
  {
    // input
    processInput(window);

    //rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //this does a full game update
    engine->Update(dt);

    //check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  engine->EngineShutDown();

  glfwTerminate();
  return 0;
}
