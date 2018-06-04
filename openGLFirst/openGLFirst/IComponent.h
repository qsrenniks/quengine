#pragma once
#include "IDrawable.h"

class IComponent : public IDrawable
{
public:
  enum ComponentType{Sprite, Physics, CompCount};

  IComponent(ComponentType compType, int z = 0);
  virtual ~IComponent();

  //virtual void Draw() const = 0;
  virtual void Update(float dt) = 0;

  void Parent(class IGameObject * parent);
  class IGameObject *GetParent() const;
  ComponentType GetComponentType() const;

private:
  class IGameObject * parent_;
  ComponentType compType_;
};

