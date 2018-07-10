#pragma once
#include <memory>
#include <string>
class IGameObject;

class IComponent 
{
public:
  IComponent(std::string& componentName, int z = 0);
  virtual ~IComponent();

  virtual void Update(float dt) = 0;
  virtual void Draw() = 0;

  virtual void Parent(IGameObject* parent);

  IGameObject *GetParent() const;

  virtual void Register();

private:
  IGameObject *parent_;
  int zDraw_;

  std::string componentName_;
};

