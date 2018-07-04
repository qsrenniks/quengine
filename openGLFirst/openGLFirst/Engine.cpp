#include "Engine.h"
#include "GameObjectSystem.h"
#include "InputSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ICommand.h"

Engine* Engine::instance_ = nullptr;

Engine::Engine()
  : cameraTransform(1.0f)
  , viewTransform(1.0f)
{
}

void Engine::AddSystem(IGameplaySystem *system)
{
  //IGameplaySystem::SystemTypes systemType = system->GetSystemType();

  //Engine* engine = instance();

   systemList_.push_back(system);
}

void Engine::AddCommand(class ICommand* command)
{
  commandStack_.push(command);
}

void Engine::Update(float dt)
{
  //Engine *engine = instance();
  if (commandStack_.empty() == false)
  {
    ICommand* command = commandStack_.top();
    command->Execute();
    commandStack_.pop();
  }


  for (IGameplaySystem* i : systemList_)
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

void Engine::EngineShutDown()
{
  for (auto system : systemList_)
  {
    system->UnloadSystem();
    delete system;
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