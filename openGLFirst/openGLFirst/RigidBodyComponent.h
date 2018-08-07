#pragma once

#include "IComponent.h"
#include "CollisionOccurence.h"
#include "Delegate.h"
#include <list>

class PhysicsComponent;
class CollisionComponent;

class RigidBodyComponent : public IComponent
{
public:
  using CollisionList = std::list<RigidBodyComponent*>;

  RigidBodyComponent(float bounce = 0.0f);
  ~RigidBodyComponent();

  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Register() override;
  virtual void Parent(IGameObject* parent) override;

  PhysicsComponent* GetPhysicsComponent();
  CollisionComponent* GetCollisionComponent();

  const float bounce_ = 0.0f;

  delegate<void(RigidBodyComponent* otherObject)> onCollisionEnter_;
  delegate<void(RigidBodyComponent* otherObject)> onCollisionExit_;

  void UpdateCollisionWith(RigidBodyComponent* otherBody, CollisionOccurence::CollisionStatus status);
  CollisionList& GetOverlappingBodies();
protected:


  CollisionList rigidBodyCollisions_;

  PhysicsComponent* physics_ = nullptr;
  CollisionComponent* collision_ = nullptr;

private:

  bool IsBodyUnique(RigidBodyComponent* otherBody);

};

