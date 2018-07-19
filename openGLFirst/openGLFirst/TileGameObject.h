#pragma once
#include "RigidBodyGameObject.h"

class SpriteComponent;
class CollisionComponent;
class PhysicsComponent;

class TileGameObject : public RigidBodyGameObject
{
public: //vars

  //static std::string TileGameObjectName;

public:
  TileGameObject();
  ~TileGameObject();

  //virtual IGameObject* Clone() override;
  virtual void Update(float dt) override;

  void OnOverlapEnter(const CollisionOccurence& otherCollider);
  void OnOverlapExit(const CollisionOccurence& otherCollider);

private:
};

