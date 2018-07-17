#pragma once

#include "IGameObject.h"
#include "GameObjectSystem.h"

class SpriteComponent;
class PhysicsComponent;
class CollisionComponent;

//struct CollisionOccurence;

class PhysicsBodyGameObject : public IGameObject
{
public:
  PhysicsBodyGameObject();
  virtual ~PhysicsBodyGameObject();

  virtual PhysicsBodyGameObject* Clone() override;

  virtual void Update(float dt) override;

  //virtual CollisionOccurence GetCollisionOccurence() override;

  void OnCollisionUpdate(CollisionOccurence otherCollider);

private:
  SpriteComponent* sprite_;
  CollisionComponent* collision_;
  PhysicsComponent* physics_;

};

