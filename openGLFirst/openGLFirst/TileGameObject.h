#pragma once
#include "IGameObject.h"

class SpriteComponent;
class CollisionComponent;
class PhysicsComponent;

class TileGameObject : public IGameObject
{
public: //vars

  //static std::string TileGameObjectName;

public:
  TileGameObject();
  ~TileGameObject();

  virtual IGameObject* Clone() override;
  virtual void Update(float dt) override;

  void OnOverlapEnter(CollisionOccurence otherCollider);
  void OnOverlapExit(CollisionOccurence otherCollider);

private:
  SpriteComponent* sprite_;
  CollisionComponent* collision_;
  PhysicsComponent* physics_;
};

