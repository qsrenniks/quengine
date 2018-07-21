#include "stdafx.h"
#include <iostream>
#include "GameObjectSystem.h"
#include "DebugGameObject.h"
#include "Engine.h"
#include <chrono>

//static Engine engine;

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}

int main()
{
  //this starts the engine up and gets it ready to deal with input and things
  Engine* engine = Engine::Instance();
  engine->Load();

  while (!glfwWindowShouldClose(engine->GetWindow()))
  {
    // input
    processInput(engine->GetWindow());

    //rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //this does a full game update
    engine->Update(0.0f);

    //check and call events and swap the buffers
    glfwSwapBuffers(engine->GetWindow());
    glfwPollEvents();
  }

  Engine::Destroy();

  glfwTerminate();
  return 0;
}
