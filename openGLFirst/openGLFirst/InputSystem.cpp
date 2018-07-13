#include "stdafx.h"
#include "InputSystem.h"
#include "Engine.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>

InputSystem::InputSystem(GLFWwindow * window) 
  : currentWindow_(window)
{

  std::ifstream fileStream(R"(ConfigFiles\inputs.json)");
  rapidjson::IStreamWrapper isw(fileStream);

  rapidjson::Document inputFile;
  inputFile.ParseStream(isw);
  
  assert(inputFile.IsObject());

  for (rapidjson::Value::ConstMemberIterator itr = inputFile.MemberBegin(); itr != inputFile.MemberEnd(); ++itr)
  {
    const rapidjson::Value& inputArray = inputFile[itr->name.GetString()];

    for (auto& v : inputArray.GetArray())
    {
      registeredInputs_.push_back(KeyActionPair(*v.GetString(), itr->name.GetString()));
    }
  }
}

void InputSystem::Load()
{

}

void InputSystem::ExecuteDelegate(int i)
{
  delegateFunctionMap_[registeredInputs_[i].ActionName_].Broadcast();

  //auto& delegateVector = delegateFunctionMap_[registeredInputs_[i].ActionName_];

  //delegateVector[i].broadcast();

  //for (unsigned int i = 0; i < delegateVector.size(); i++)
  //{
  //  delegateVector[i].broadcast();
  //}
  
}

void InputSystem::Update(float dt)
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

void InputSystem::Unload()
{

}

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
