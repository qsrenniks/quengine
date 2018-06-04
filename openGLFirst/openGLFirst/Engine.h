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

  void EngineLoad();

  void Update(float dt);
  
  //TODO: Remove this from Engine and place in a more camera type system.
  glm::mat4& GetCameraTransform();
  glm::mat4& GetViewTransform();

protected:
  Engine();

private:
  static Engine* instance_;
  IGameplaySystem * systemList_[IGameplaySystem::NumOfSystems];


  //struct DrawFunction
  //{
  //  template<class UserClass, typename Method>
  //  DrawFunction(unsigned int z, UserClass userClass, Method function)
  //    : z_(z)
  //    , drawFunction_(userClass, function)
  //  {}

  //  unsigned int z_;
  //  Delegate<void> drawFunction_;
  //};

  //struct DrawFunctionComparator
  //{
  //  bool operator()(const DrawFunction* a, const DrawFunction* b)
  //  {
  //    return a->z_ < b->z_;
  //  }
  //};

  //draw list

  //TODO: free memory allocated in this array
  //std::multiset<DrawFunction*, DrawFunctionComparator> drawList_;
  //update list

  //TODO: free memory allocated in this object
  //DynamicDelegateSingleParam<void, float> updateList_;

  glm::mat4 cameraTransform;
  glm::mat4 viewTransform;

};


