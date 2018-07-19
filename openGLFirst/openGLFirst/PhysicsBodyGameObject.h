#pragma once

#include "RigidBodyGameObject.h"

class PhysicsBodyGameObject : public RigidBodyGameObject
{
public:
  PhysicsBodyGameObject();
  virtual ~PhysicsBodyGameObject();

  //virtual PhysicsBodyGameObject* Clone() override;

  virtual void Update(float dt) override;

  //virtual CollisionOccurence GetCollisionOccurence() override;

  void OnCollisionUpdate(const CollisionOccurence& otherCollider);

private:

};

