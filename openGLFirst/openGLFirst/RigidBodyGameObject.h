#pragma once
#include "IGameObject.h"

class PhysicsComponent;
class CollisionComponent;

//
// This class is not meant to be instantiated seperately.
// Derive then instantiate.
//
class RigidBodyGameObject : public IGameObject
{
public:
  RigidBodyGameObject();
  virtual ~RigidBodyGameObject();

  void CheckCollisionAgainst(RigidBodyGameObject* otherRigidBody);

  CollisionComponent* GetCollisionComponent();
  PhysicsComponent* GetPhysicsComponent();
protected:
  PhysicsComponent * physics_;
  CollisionComponent *collision_;
};
