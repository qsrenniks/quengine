#pragma once
#include "IGameObject.h"

class SpriteComponent;
class CollisionComponent;
class PhysicsComponent;
class RigidBodyComponent;

class TileGameObject : public IGameObject
{
public:
  TileGameObject();
  ~TileGameObject();

  //virtual IGameObject* Clone() override;
  virtual void Update(float dt) override;

  void OnOverlapEnter(const CollisionOccurence& otherCollider);
  void OnOverlapExit(const CollisionOccurence& otherCollider);

protected:

  RigidBodyComponent * rigidBodyComponent_ = nullptr;

private:
};

