#include "Engine.h"
#include "GameObjectSystem.h"
#include "InputSystem.h"
#include "MemoryModule.h"
#include <glm/gtc/matrix_transform.hpp>

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

void Engine::AddModule(IModule *module)
{
  moduleList_.push_back(module);
}

void Engine::Update(float dt)
{
  //Engine *engine = instance();

  for (IGameplaySystem* i : systemList_)
  {
    i->UpdateSystem(dt);
  }
}

glm::mat4& Engine::GetCameraTransform()
{
  Engine* engine = instance();

  return engine->cameraTransform;
}

glm::mat4& Engine::GetViewTransform()
{
  return instance()->viewTransform;
}

void Engine::SetWindow(GLFWwindow * window)
{
  currentWindow_ = window;
}

void Engine::EngineShutDown()
{
  for (auto system : systemList_)
  {
    system->UnloadSystem();
    delete system;
  }

  for (auto module : moduleList_)
  {
    module->UnloadModule();
    delete module;
  }


  delete instance_;
}

void Engine::EngineLoad()
{
  AddModule(new MemoryModule(100));
  AddSystem(new InputSystem(currentWindow_));
  AddSystem(new GameObjectSystem());

  for (auto system : systemList_)
  {
    system->LoadSystem();
  }

  for (auto module : moduleList_)
  {
    module->LoadModule();
  }
}