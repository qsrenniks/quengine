#pragma once
#include "IComponent.h"
#include <glm/glm.hpp>

class CollisionComponent;
class PhysicsComponent;
class RigidBodyGameObject;
//
// This class is created in the event of a collision in the update loop. 
// if a collision is detected this class is created then pushed onto the gameobjectsystem to later be resolved
//
struct CollisionOccurence
{
public:
  enum class CollisionStatus : int { NOT_COLLIDING, COLLIDING, INVALID };

  CollisionOccurence(bool isValid = false)
    : collisionStatus_(CollisionStatus::NOT_COLLIDING)
    , mtv_(0.0f)
    //, halfMtv_(0.0f)
    , isValid_(isValid)
  {
  }

  void ConstructNonCollisionOccurence(RigidBodyGameObject* objectA, RigidBodyGameObject* objectB, CollisionStatus collisionStatus);

  void Resolve();

  float penetration_;

  float restitution_;
  glm::vec2 collisionNormal_;

  //glm::vec2 halfMtv_;
  CollisionStatus collisionStatus_;

  RigidBodyGameObject* objectA_ = nullptr;

  RigidBodyGameObject* objectB_ = nullptr;

  bool IsValid();
  void SetValid(bool validity);

  bool operator==(const CollisionOccurence& otherCollision) const;

  //CollisionOccurence operator-();

  bool isResolved_ = false;

private:

  void ResolveVelocities(float dt);
  void ResolveInterpenetration(float dt);

  bool isValid_ = false;
};
