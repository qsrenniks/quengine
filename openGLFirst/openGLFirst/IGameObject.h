#pragma once

#include <array>
#include "IComponent.h"
#include <glm/glm.hpp>
#include "Delegate.h"

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
  void AddComponent(std::unique_ptr<Component>& component, _Types&&... _Args)
  {
    //this expands the _Types pack into the parameters passed in to construct the object 
    component = std::make_unique<Component>(_Args...);

    component->Parent(this);
    //drawDelegate_.addFunction(dynamic_cast<IDrawable*>(component), &IDrawable::Draw); 
    component->Register();
    
    //componentUpdateList_.AddFunction(component.get(), &Component::Update);
    //componentDrawList_.AddFunction(component.get(), &Component::Draw);
  }

  void UpdateGameObject(float dt);

  void DestroyGameObject();

  bool IsMarkedForDestroy();

  virtual IGameObject *Clone() = 0;

  virtual void Update(float dt) = 0;

  glm::mat4& GetTransform();

  delegate<void(float)>& GetUpdateList();
  delegate<void(float)>& GetComponentUpdateList();
  delegate<void(void)>& GetDrawList();

private:
  delegate<void(float)> gameObjectUpdateList_;

  delegate<void(float)> componentUpdateList_;

  delegate<void(void)> componentDrawList_;

  glm::mat4 transform_;
  
  bool markForDestroy_ = false;
};

