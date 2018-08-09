#pragma once

class CollisionComponent;
struct CollisionOccurence;

//
// Base class for collision profile. Derive from this to create a new profile with custom collision detection methods
//
// NP Stands for Narrow Phase
//
class NPCollisionProfile
{
public:

  NPCollisionProfile();
  virtual void IsProfileCollidingWith(NPCollisionProfile* otherProfile, CollisionOccurence& collOcc) const = 0;

  CollisionComponent* GetCollisionComponent();
  void SetCollisionComponent(CollisionComponent* thisCollider);

protected:
  CollisionComponent * collisionComponent_ = nullptr;
};
