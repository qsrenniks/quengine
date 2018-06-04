#pragma once
#include "IGameObject.h"

class BackgroundGameObject : public IGameObject
{
public:
  BackgroundGameObject();

  virtual ~BackgroundGameObject();

  virtual void Update(float dt) override;


};