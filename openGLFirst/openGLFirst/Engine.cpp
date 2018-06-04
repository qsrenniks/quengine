#include "Engine.h"
#include <glm/gtc/matrix_transform.hpp>

Engine* Engine::instance_ = nullptr;

Engine::Engine()
  : cameraTransform(1.0f)
  , viewTransform(1.0f)
{
}

void Engine::AddSystem(IGameplaySystem *system)
{
  IGameplaySystem::SystemTypes systemType = system->GetSystemType();

  Engine* engine = instance();

  engine->systemList_[systemType] = system;
}

void Engine::AddModule(IModule *module)
{
  
}

void Engine::Update(float dt)
{
  Engine *engine = instance();

  for (IGameplaySystem* i : engine->systemList_)
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

void Engine::EngineShutDown()
{
  for (unsigned int i = 0; i < IGameplaySystem::NumOfSystems; i++)
  {
    instance_->systemList_[i]->UnloadSystem();
    delete instance_->systemList_[i];
  }

  delete instance_;
}

void Engine::EngineLoad()
{
  for (unsigned int i = 0; i < IGameplaySystem::NumOfSystems; i++)
  {
    instance_->systemList_[i]->LoadSystem();
  }
}