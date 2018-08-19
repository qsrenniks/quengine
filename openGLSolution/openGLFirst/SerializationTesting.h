#pragma once
#include "IGameObject.h"

class SerializationTesting : public IGameObject
{
public:
  SerializationTesting();
  ~SerializationTesting();

  virtual void Update(float dt) override;

private:
  float health = 3.14159f;
};

