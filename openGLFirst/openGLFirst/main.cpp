#include "stdafx.h"
#include <iostream>
#include "GameObjectSystem.h"
#include "DebugGameObject.h"
#include "Engine.h"
#include <chrono>

static GLFWwindow* window;
//static Engine engine;

static int frames = 0;

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

  window = glfwCreateWindow(900, 900, "LearnOpenGL", nullptr, nullptr);

  if (window == nullptr)
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

  //this starts the engine up and gets it ready to deal with input and things
  Engine* engine = Engine::Instance();
  engine->SetWindow(window);
  engine->EngineLoad();

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
