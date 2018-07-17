#pragma once

#include "IGameObject.h"

class SpriteComponent;
class PhysicsComponent;
class CollisionComponent;

class PhysicsBodyGameObject : public IGameObject
{
public:
  PhysicsBodyGameObject();
  virtual ~PhysicsBodyGameObject();

  virtual PhysicsBodyGameObject* Clone() override;

  virtual void Update(float dt) override;

  //virtual CollisionOccurence GetCollisionOccurence() override;

  void OnCollisionUpdate(CollisionComponent* otherCollider);

private:
  SpriteComponent* sprite_;
  CollisionComponent* collision_;
  PhysicsComponent* physics_;

};

