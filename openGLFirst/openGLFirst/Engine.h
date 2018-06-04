#pragma once
#include "IGameplaySystem.h"
#include "IModule.h"
#include "Delegate.h"
#include <glm/glm.hpp>
#include <array>
#include <vector>
#include <set>

class Engine
{
public:

  //Engine();

  static Engine* instance()
  {
    if (instance_ == nullptr)
    {
      instance_ = new Engine();
    }

    return instance_;
  }

  void EngineShutDown();
  void AddSystem(IGameplaySystem *system);
  
  void AddModule(IModule *module);

  template <typename T>
  T* GetSystem()
  {
    for (auto sysIter : systemList_)
    {
      T *system = nullptr;
      if (sysIter != nullptr)
      {
        system = dynamic_cast<T*>(sysIter);
      }

      if (system != nullptr)
      {
        return system;
      }
    }

    return nullptr;
  };

  template <typename T>
  T* GetModule()
  {
    for (auto moduleIter : moduleList_)
    {
      T *module = nullptr;
    }
  }

  void EngineLoad();

  void Update(float dt);
  
  //TODO: Remove this from Engine and place in a more camera type system.
  glm::mat4& GetCameraTransform();
  glm::mat4& GetViewTransform();

  void SetWindow(struct GLFWwindow * window);

protected:
  Engine();

private:
  static Engine* instance_;
  struct GLFWwindow * currentWindow_;

  std::vector<IGameplaySystem*> systemList_;
  std::vector<IModule*> moduleList_;

  glm::mat4 cameraTransform;
  glm::mat4 viewTransform;

};


