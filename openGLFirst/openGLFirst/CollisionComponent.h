#pragma once
#include "IComponent.h"

class CollisionComponent;
class IGameObject;

class CollisionProfile
{
public:

  CollisionProfile(CollisionComponent *&component);
  virtual bool IsProfileCollidingWith(CollisionProfile *otherProfile) = 0;

  CollisionComponent *GetComponentParent();

protected:
  CollisionComponent *&component_;
};

class SquareCollisionProfile : public CollisionProfile
{
public:
  SquareCollisionProfile(CollisionComponent *&component);

  virtual bool IsProfileCollidingWith(CollisionProfile *otherProfile) override;

private:
};

class CollisionComponent : public IComponent
{
public:
  CollisionComponent(CollisionProfile * = nullptr);
  ~CollisionComponent();

  virtual void Update(float dt) override;
  virtual void Draw() override;

  virtual void Parent(IGameObject *parent) override;

  virtual void Register() override;

  bool IsCollidingWith(CollisionComponent * otherCollider);

private:

  CollisionProfile * collisionProfile_;
};

