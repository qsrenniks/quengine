#pragma once
#include "IComponent.h"

class CollisionProfile
{
  virtual bool IsProfileCollidingWith(CollisionProfile* otherProfile) = 0;
};

class SquareCollisionProfile : public CollisionProfile
{

};

class CollisionComponent : public IComponent
{
public:
  CollisionComponent(CollisionProfile *profile = nullptr);
  ~CollisionComponent();

  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Parent(class IGameObject * parent) override;

  virtual void Register() override;

  bool IsCollidingWith(CollisionComponent *otherCollider);

private:

  CollisionProfile *collisionProfile_;
};

