#pragma once
#include "IGameObject.h"

class SerializationTesting : public IGameObject
{
public:
  SerializationTesting();
  ~SerializationTesting();

  virtual void Update(float dt) override;


  virtual void Serialize(rapidjson::Document& doc) override;
  virtual void Deserialize(rapidjson::Document& doc) override;

private:
  float health = 3.14159f;
};

