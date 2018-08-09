#pragma once
#include "ISystem.h"

class IGameplaySystem : public ISystem
{
public:

  //enum SystemTypes { InputSystem, GameObjectSystem, NumOfSystems };

  //IGameplaySystem(SystemTypes systemType);
  IGameplaySystem() = default;

  virtual ~IGameplaySystem() = default;

  virtual void Update(float dt) = 0;
  //SystemTypes GetSystemType() const { return systemType_; };

private:
  //SystemTypes systemType_;
};