#pragma once
#include "IGameplaySystem.h"
#include "Delegate.h"
#include <glm/glm.hpp>
#include <array>
#include <vector>
#include <stack>
#include <set>

class Engine
{
public:

  //Engine();

  static Engine* Instance()
  {
    if (instance_ == nullptr)
    {
      instance_ = new Engine();
    }

    return instance_;
  }

  void EngineShutDown();

  //void AddSystem(IGameplaySystem* system);
  
  void AddCommand(class ICommand* command);

  //template <typename T>
  //T* GetSystem()
  //{
  //  T* tempPtr = nullptr;

  //  for (auto system : systemList_)
  //  {
  //    if (system == nullptr)
  //    {
  //      continue;
  //    }

  //    if ((tempPtr = dynamic_cast<T*>(system)) != nullptr)
  //    {
  //      break;
  //    }
  //  }

  //  return tempPtr;
  //};

  void EngineLoad();

  void Update(float dt);
  
  //TODO: Remove this from Engine and place in a more camera type system.
  glm::mat4& GetCameraTransform();
  glm::mat4& GetViewTransform();

  void SetWindow(struct GLFWwindow * window);

  struct GLFWwindow* GetWindow();

  class InputSystem* inputSystem_;
  class GameObjectSystem* gameObjectSystem_;

protected:
  Engine();
  ~Engine();

private:

  std::vector<class ICommand*> commandStack_;

  static Engine* instance_;
  struct GLFWwindow * currentWindow_;

  //std::vector<IGameplaySystem*> systemList_;

  glm::mat4 cameraTransform_;
  glm::mat4 viewTransform_;

};


