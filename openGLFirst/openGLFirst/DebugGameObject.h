#pragma once
#include "IGameObject.h"
#include "CollisionComponent.h"

class SpriteComponent;
class PhysicsComponent;
class CollisionComponent;

class DebugGameObject : public IGameObject
{
public: //public vars

  static std::string DebugGameObjectName;

public:
  DebugGameObject();
  virtual ~DebugGameObject();

  virtual IGameObject* Clone() override;
  virtual void Update(float dt) override;

  void WKeyPress();

  void SKeyPress();
  void DKeyPress();
  void AKeyPress();

  //virtual CollisionOccurence GetCollisionOccurence() override;

private:
  SpriteComponent* sprite_;
  PhysicsComponent* physics_;
  CollisionComponent* collision_;

  void OnCollisionUpdate(CollisionOccurence otherCollider);
  void OnCollision(CollisionOccurence otherCollider);
  void OnExitCollision(CollisionOccurence otherCollider);
protected:

};

