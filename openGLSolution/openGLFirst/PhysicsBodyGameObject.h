#pragma once

#include "IGameObject.h"

class RigidBodyComponent;

class PhysicsBodyGameObject : public IGameObject
{
public:
  PhysicsBodyGameObject();
  virtual ~PhysicsBodyGameObject();

  virtual void Update(float dt) override;

  virtual void Serialize(rapidjson::Document& doc) override;
  virtual void Deserialize(rapidjson::Document& doc) override;

protected:

  RigidBodyComponent* rigidBody_ = nullptr;

private:
  


};

