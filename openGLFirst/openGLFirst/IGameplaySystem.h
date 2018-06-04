#pragma once
#include "IDrawable.h"
class IGameplaySystem : public IDrawable
{
public:

  enum SystemTypes { InputSystem, GameObjectSystem, NumOfSystems };

  IGameplaySystem(SystemTypes systemType);

  virtual ~IGameplaySystem() {};

  virtual void LoadSystem() = 0;
  virtual void UpdateSystem(float dt) = 0;
  virtual void UnloadSystem() = 0;

  SystemTypes GetSystemType() const { return systemType_; };

private:
  SystemTypes systemType_;
};