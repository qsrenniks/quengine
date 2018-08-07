#pragma once

#include "IGameObject.h"

class RigidBodyComponent;

class PhysicsBodyGameObject : public IGameObject
{
public:
  PhysicsBodyGameObject();
  virtual ~PhysicsBodyGameObject();

  virtual void Update(float dt) override;
  
protected:

  RigidBodyComponent* rigidBody_ = nullptr;

private:
  


};

