#pragma once

class IComponent 
{
public:
  IComponent(int z = 0);
  virtual ~IComponent();

  virtual void Update(float dt) = 0;
  virtual void Draw() = 0;

  virtual void Parent(class IGameObject * parent);

  class IGameObject *GetParent() const;

  virtual void Register();

private:
  class IGameObject * parent_;
  int zDraw_;
};

