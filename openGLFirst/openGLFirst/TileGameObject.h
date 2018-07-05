#pragma once
#include "IGameObject.h"

class SpriteComponent;

class TileGameObject : public IGameObject
{
public:
  TileGameObject();
  ~TileGameObject();

  virtual IGameObject *Clone() override;
  virtual void Update(float dt) override;

private:
  SpriteComponent *sprite_;
};

