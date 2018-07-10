#include "stdafx.h"
#include "Engine.h"
#include "GameObjectSystem.h"
#include "InputSystem.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ICommand.h"
#include <memory>

Engine* Engine::instance_ = nullptr;

Engine::Engine()
  : cameraTransform_(1.0f)
  , viewTransform_(1.0f)
{
}

//void Engine::AddSystem(IGameplaySystem* system)
//{
//  systemList_.push_back(system);
//}

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

  inputSystem_->UpdateSystem(dt);
  gameObjectSystem_->UpdateSystem(dt);
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
  inputSystem_->UnloadSystem();
  gameObjectSystem_->UnloadSystem();
}

void Engine::EngineShutDown()
{
  delete instance_;
}

void Engine::EngineLoad()
{
  //AddSystem(new InputSystem(currentWindow_));
  //AddSystem(new GameObjectSystem());

  inputSystem_ = new InputSystem(currentWindow_);
  gameObjectSystem_ = new GameObjectSystem();

  inputSystem_->LoadSystem();
  gameObjectSystem_->LoadSystem();

}