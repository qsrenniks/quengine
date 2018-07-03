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

  //template <typename T>
  void AddComponent(IComponent *component)
  {
    component->Parent(this);
    //drawDelegate_.addFunction(dynamic_cast<IDrawable*>(component), &IDrawable::Draw); 
    componentUpdateList_.AddFunction(component, &IComponent::Update);
    componentDrawList_.AddFunction(component, &IComponent::Draw);
  }

  void UpdateGameObject(float dt);

  virtual void Update(float dt) = 0;

  glm::mat4& GetTransform();

private:
  delegate<void(float)> gameObjectUpdateList_;

  delegate<void(float)> componentUpdateList_;
  delegate<void(void)> componentDrawList_;

  glm::mat4 transform_;
};

