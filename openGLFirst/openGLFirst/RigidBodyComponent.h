#pragma once

#include "IComponent.h"

class PhysicsComponent;
class CollisionComponent;

class RigidBodyComponent : public IComponent
{
public:
  RigidBodyComponent(float bounce = 0.0f);
  ~RigidBodyComponent();

  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Register() override;
  virtual void Parent(IGameObject* parent) override;

  PhysicsComponent* GetPhysicsComponent();
  CollisionComponent* GetCollisionComponent();

  const float bounce_ = 0.0f;
protected:

  PhysicsComponent* physics_ = nullptr;
  CollisionComponent* collision_ = nullptr;

private:

};

