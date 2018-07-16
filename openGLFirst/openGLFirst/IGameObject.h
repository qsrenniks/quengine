#pragma once

#include <array>
#include "IComponent.h"
#include "Delegate.h"
#include "Transform.h"

struct CollisionOccurence;

class IGameObject
{
public:

  IGameObject();
  virtual ~IGameObject();

  //void AddComponent(IComponent *component);

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

  void UpdateGameObject(float dt);
  void DestroyGameObject();
  bool IsMarkedForDestroy();
  virtual IGameObject* Clone() = 0;
  virtual void Update(float dt) = 0;
  Transform& GetTransform();

  delegate<void(float)>& GetComponentUpdateList();
  delegate<void(void)>& GetDrawList();

  virtual bool PreventPhysics();

  virtual CollisionOccurence GetCollisionOccurence();

private:
  
  delegate<void(float)> componentUpdateList_;
  delegate<void(void)> componentDrawList_;

  using ComponentList = std::vector<IComponent*>;

  ComponentList componentList_;

  Transform transform_;
  
  bool markForDestroy_ = false;
};

struct CollisionOccurence
{
  enum class CollisionStatus : int { NOT_COLLIDING, COLLIDING, TOUCHING };

  CollisionOccurence(bool isValid = false)
    : collisionStatus_(CollisionStatus::COLLIDING)
    , mtv_(0)
    , isValid_(isValid)
  {
  }

  CollisionStatus collisionStatus_;

  glm::vec2 mtv_;

  bool IsValid();
  void SetValid(bool validity);
private:

  bool isValid_ = false;
};