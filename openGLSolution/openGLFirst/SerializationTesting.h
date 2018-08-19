#pragma once
#include "IGameObject.h"

class SerializationTesting : public IGameObject
{
public:
  SerializationTesting();
  ~SerializationTesting();

private:
  float health = 3.14159f;
};

