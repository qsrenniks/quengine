#pragma once
#include "IGameObject.h"

class TileGameObject : public IGameObject
{
public:
  TileGameObject();
  ~TileGameObject();

  virtual IGameObject *Clone() override;
  virtual void Update(float dt) override;

private:
  std::unique_ptr<class SpriteComponent> sprite_;
};

