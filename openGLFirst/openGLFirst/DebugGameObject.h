#pragma once
#include "IGameObject.h"
#include "CollisionComponent.h"

class SpriteComponent;
class PhysicsComponent;
class CollisionComponent;

class DebugGameObject : public IGameObject
{
public:
  DebugGameObject();
  virtual ~DebugGameObject();

  virtual IGameObject* Clone() override;
  virtual void Update(float dt) override;

  void WKeyPress();

  void SKeyPress();
  void DKeyPress();
  void AKeyPress();



private:
  SpriteComponent* sprite_;
  PhysicsComponent* physics_;
  CollisionComponent* collision_;

  void OnCollisionUpdate(CollisionComponent::CollidingWithList& );
  void OnCollision(CollisionComponent* otherCollider);
  void OnExitCollision(CollisionComponent* otherCollider);
protected:

};

