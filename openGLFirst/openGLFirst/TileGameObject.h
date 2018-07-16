#pragma once
#include "IGameObject.h"

class SpriteComponent;
class CollisionComponent;
class PhysicsComponent;

class TileGameObject : public IGameObject
{
public:
  TileGameObject();
  ~TileGameObject();


  virtual IGameObject* Clone() override;
  virtual void Update(float dt) override;

  void OnOverlapEnter(CollisionComponent* otherCollider);
  void OnOverlapExit(CollisionComponent* otherCollider);
private:
  SpriteComponent* sprite_;
  CollisionComponent* collision_;
  PhysicsComponent* physics_;
};

