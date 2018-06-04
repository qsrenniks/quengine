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

    updateDelegate_.addFunction(component, &IComponent::Update);
    drawDelegate_.addFunction(dynamic_cast<IDrawable*>(component), &IDrawable::Draw);
  }

  void UpdateGameObject(float dt);
  void DrawGameObject();

  virtual void Update(float dt) = 0;

  glm::mat4& GetTransform();

private:
  //typedef std::vector<delegate<void(float)>> UpdateDelegateList;
  delegate<void(float)> updateDelegate_;

  delegate<void()> drawDelegate_;

  glm::mat4 transform_;
};

