#pragma once

class IGameplaySystem 
{
public:

  //enum SystemTypes { InputSystem, GameObjectSystem, NumOfSystems };

  //IGameplaySystem(SystemTypes systemType);
  IGameplaySystem() = default;

  virtual ~IGameplaySystem() = default;

  virtual void Load() = 0;
  virtual void Update(float dt) = 0;
  virtual void Unload() = 0;

  //SystemTypes GetSystemType() const { return systemType_; };

private:
  //SystemTypes systemType_;
};