#pragma once
#include <memory>

class IGameObject;

class IComponent 
{
public:
  IComponent(int z = 0);
  virtual ~IComponent();

  virtual void Update(float dt) = 0;
  virtual void Draw() = 0;

  virtual void Parent(IGameObject* parent);

  IGameObject *GetParent() const;

  virtual void Register();

private:
  IGameObject *parent_;
  int zDraw_;
};

