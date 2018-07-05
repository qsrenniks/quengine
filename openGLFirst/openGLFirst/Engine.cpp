#include "stdafx.h"
#include "Engine.h"
#include "GameObjectSystem.h"
#include "InputSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ICommand.h"
#include <memory>

Engine* Engine::instance_ = nullptr;

Engine::Engine()
  : cameraTransform(1.0f)
  , viewTransform(1.0f)
{
}

void Engine::AddSystem(IGameplaySystem* system)
{
  systemList_.push_back(system);
}

void Engine::AddCommand(class ICommand* command)
{
  commandStack_.push_back(command);
}

void Engine::Update(float dt)
{
  //Engine *engine = instance();
  if (commandStack_.empty() == false)
  {
    auto commandExecuteLambda = [&](ICommand *i) {i->Execute(); };
    std::for_each(commandStack_.begin(), commandStack_.end(), commandExecuteLambda);

    commandStack_.clear();
  }

  for (auto i : systemList_)
  {
    i->UpdateSystem(dt);
  }
}

glm::mat4& Engine::GetCameraTransform()
{
  Engine* engine = Instance();

  return engine->cameraTransform;
}

glm::mat4& Engine::GetViewTransform()
{
  return Instance()->viewTransform;
}

void Engine::SetWindow(GLFWwindow * window)
{
  currentWindow_ = window;
}

struct GLFWwindow* Engine::GetWindow()
{
  return currentWindow_;
}

Engine::~Engine()
{

}

void Engine::EngineShutDown()
{
  for (auto& system : systemList_)
  {
    system->UnloadSystem();
    delete system;
    system = nullptr;
  }

  delete instance_;
}

void Engine::EngineLoad()
{
  AddSystem(new InputSystem(currentWindow_));
  AddSystem(new GameObjectSystem());

  for (auto system : systemList_)
  {
    system->LoadSystem();
  }

}