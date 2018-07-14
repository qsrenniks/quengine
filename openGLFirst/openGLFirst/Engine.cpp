#include "stdafx.h"
#include "Engine.h"
//#include "GameObjectSystem.h"
#include "InputSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ICommand.h"
#include <memory>

Engine* Engine::instance_ = nullptr;

Engine::Engine(GLFWwindow *currentWindow)
  : cameraTransform_(1.0f)
  , viewTransform_(1.0f)
  , currentWindow_(currentWindow)
  , inputSystem_(currentWindow_)
  , gameObjectSystem_()
{
}

void Engine::AddCommand(ICommand* command)
{
  commandStack_.push_back(command);
}

void Engine::Update(float dt)
{
  if (commandStack_.empty() == false)
  {
    auto commandExecuteLambda = [&](ICommand* i) {i->Execute(); };
    std::for_each(commandStack_.begin(), commandStack_.end(), commandExecuteLambda);

    commandStack_.clear();
  }

  inputSystem_.Update(dt);
  gameObjectSystem_.Update(dt);
}

glm::mat4& Engine::GetCameraTransform()
{
  Engine* engine = Instance();

  return engine->cameraTransform_;
}

glm::mat4& Engine::GetViewTransform()
{
  return Instance()->viewTransform_;
}

void Engine::SetWindow(GLFWwindow* window)
{
  currentWindow_ = window;
}

GLFWwindow* Engine::GetWindow()
{
  return currentWindow_;
}

InputSystem* Engine::GetInputSystem()
{
  return &inputSystem_;
}

GameObjectSystem* Engine::GetGameObjectSystem()
{
  return &gameObjectSystem_;
}

Engine::~Engine()
{
  ShutDown();
}

void Engine::Destroy()
{
  delete instance_;
}

Engine* Engine::Instance(GLFWwindow* currentWindow)
{
  if (instance_ == nullptr)
  {
    instance_ = new Engine(currentWindow);
  }

  return instance_;
}

void Engine::ShutDown()
{
  inputSystem_.Unload();
  gameObjectSystem_.Unload();
}

void Engine::Load()
{
  inputSystem_.Load();
  gameObjectSystem_.Load();
}