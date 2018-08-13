#pragma once

struct CollisionOccurence;
class CollisionComponent;
enum class CollisionStatus : int;

class CollisionProfile
{
public:
  CollisionProfile();

  virtual CollisionStatus IsProfileCollidingWith(CollisionProfile* otherProfile) const = 0;

  void SetCollisionComponent(CollisionComponent* thisCollider);
  CollisionComponent* GetCollisionComponent();

  virtual ~CollisionProfile();
protected:

  CollisionComponent * collisionComponent_ = nullptr;
};

