#pragma once

#include <array>
#include "IComponent.h"
#include "Delegate.h"
#include "Transform.h"
#include <string>

struct CollisionOccurence;
class SpriteComponent;

class IGameObject
{
public:

  IGameObject();
  virtual ~IGameObject();

  //Add Component
  //
  // _Types: Packed parameters for component constructor.
  template <typename Component, class... _Types>
  void AddComponent(Component*& component, _Types&&... _Args)
  {
    //this expands the _Types pack into the parameters passed in to construct the object 
    component = new Component(_Args...);

    component->Parent(this);

    component->Register();
    
    componentList_.push_back(component);
  }

  template<typename T>
  T* GetComponent()
  {
    T* tempPtr = nullptr;

    for (auto component : componentList_)
    {
      if ((tempPtr = dynamic_cast<T*>(component)) != nullptr)
      {
        break;
      }
    }

    return tempPtr;
  }

  template<>
  SpriteComponent* GetComponent<SpriteComponent>()
  {
    return sprite_;
  }

  void UpdateGameObject(float dt);
  void DestroyGameObject();
  bool IsMarkedForDestroy();
  //virtual IGameObject* Clone() = 0;
  virtual void Update(float dt) = 0;
  Transform& GetTransform();
  SpriteComponent* GetSpriteComponent();


  delegate<void(float)>& GetComponentUpdateList();
  delegate<void(void)>& GetDrawList();

  //virtual CollisionOccurence GetCollisionOccurence();
  const std::string& GetObjectName();

protected:

  Transform transform_;
  SpriteComponent * sprite_;
  //std::string objectName_;

private:

  delegate<void(float)> componentUpdateList_;
  delegate<void(void)> componentDrawList_;

  using ComponentList = std::vector<IComponent*>;

  ComponentList componentList_;
  bool markForDestroy_ = false;
};

