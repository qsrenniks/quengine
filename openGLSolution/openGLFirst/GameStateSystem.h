#pragma once
#include "ISystem.h"

class GameStateSystem : public ISystem
{
public:
  GameStateSystem();
  ~GameStateSystem();

  virtual void Load() override;
  virtual void Unload() override;

};

