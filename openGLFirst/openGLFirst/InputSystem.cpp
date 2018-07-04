#include "InputSystem.h"
#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include "Engine.h"
#include "rapidjson/document.h"
#include <fstream>

InputSystem::InputSystem(GLFWwindow * window) 
  //: IGameplaySystem(IGameplaySystem::InputSystem)
  : currentWindow_(window)
{
  //this should determine what symbols are queried
  //if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
  //{
  //  glfwSetWindowShouldClose(window, true);
  //}


  //rapidjson::Document inputFile;
  //std::ifstream configInputFile("ConfigFile/input.txt");
  ////configInputFile;
  //

  //inputFile.ParseStream(configInputFile);
  //inputFile.

  registeredInputs_.push_back(KeyActionPair(GLFW_KEY_W, "Move Up"));
  registeredInputs_.push_back(KeyActionPair(GLFW_KEY_A, "Move Left"));
  registeredInputs_.push_back(KeyActionPair(GLFW_KEY_S, "Move Down"));
  registeredInputs_.push_back(KeyActionPair(GLFW_KEY_D, "Move Right"));
}

void InputSystem::LoadSystem()
{

}

void InputSystem::ExecuteDelegate(int i)
{
  delegateFunctionMap_[registeredInputs_[i].ActionName_].broadcast();

  //auto& delegateVector = delegateFunctionMap_[registeredInputs_[i].ActionName_];

  //delegateVector[i].broadcast();

  //for (unsigned int i = 0; i < delegateVector.size(); i++)
  //{
  //  delegateVector[i].broadcast();
  //}
  
}

void InputSystem::UpdateSystem(float dt)
{
  for (unsigned int i = 0; i < registeredInputs_.size(); i++)
  {
    //if registered action is being activated.
    if (glfwGetKey(currentWindow_, registeredInputs_[i].Key_) == GLFW_PRESS)
    {
      //ExecuteDelegate(i);
      if (registeredInputs_[i].consumeInput_ == false)
      {
        ExecuteDelegate(i);
      }
      else if(registeredInputs_[i].executeDelegate_ == true)
      {
        registeredInputs_[i].executeDelegate_ = false;
        ExecuteDelegate(i);
      }
    }

    if (glfwGetKey(currentWindow_, registeredInputs_[i].Key_) == GLFW_RELEASE)
    {
      registeredInputs_[i].executeDelegate_ = true;
    }
  }
}

void InputSystem::UnloadSystem()
{

}

//void InputSystem::Draw()
//{
//
//}

static float dt = 0.0166667f;

void InputSystem::MoveCameraUp()
{
  Engine::Instance()->GetCameraTransform()[3].y += dt;
}

void InputSystem::MoveCameraDown()
{
  Engine::Instance()->GetCameraTransform()[3].y += -dt;
}

void InputSystem::MoveCameraLeft()
{
  Engine::Instance()->GetCameraTransform()[3].x += -dt;
}

void InputSystem::MoveCameraRight()
{
  Engine::Instance()->GetCameraTransform()[3].x += dt;
}
